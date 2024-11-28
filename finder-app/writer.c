#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

// Function to create directories if they don't exist
void create_directory(const char *path) {
    char *dir = strdup(path);
    if (dir == NULL) {
        syslog(LOG_ERR, "Memory allocation failed.");
        exit(1);
    }

    // Find the last slash character
    char *last_slash = strrchr(dir, '/');
    if (last_slash) {
        // Terminate the string at the last slash
        *last_slash = '\0';
        // Create the directory (if it doesn't exist)
        if (mkdir(dir, 0777) == -1) {
            if (errno != EEXIST) {
                syslog(LOG_ERR, "Could not create directory: %s", dir);
                free(dir);
                exit(1);
            }
        }
    }
    free(dir);
}

int main(int argc, char *argv[]) {
    // Open syslog for logging with LOG_USER facility
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    // Check if the correct number of arguments are provided
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Two arguments are required. Usage: writer <file_path> <string_to_write>");
        fprintf(stderr, "Error: Two arguments are required. Usage: writer <file_path> <string_to_write>\n");
        closelog();
        return 1;
    }

    // Get file path and string to write
    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Create the directory (if it doesn't exist)
    create_directory(writefile);

    // Open the file for writing
    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Could not create or open the file %s.", writefile);
        fprintf(stderr, "Error: Could not create or open the file %s.\n", writefile);
        closelog();
        return 1;
    }

    // Write the string to the file
    fprintf(file, "%s", writestr);

    // Check if writing was successful
    if (ferror(file)) {
        syslog(LOG_ERR, "Error: Could not write to the file %s.", writefile);
        fprintf(stderr, "Error: Could not write to the file %s.\n", writefile);
        fclose(file);
        closelog();
        return 1;
    }

    // Log the success message with LOG_DEBUG level
    syslog(LOG_DEBUG, "Writing \"%s\" to \"%s\".", writestr, writefile);

    // Close the file
    fclose(file);

    // Close syslog
    closelog();

    return 0;
}

