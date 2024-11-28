# Define the cross-compiler prefix (empty for native build, set to cross-compiler toolchain for cross-compilation)
CROSS_COMPILE ?= 

# Define the compiler and linker (with cross-compiler prefix if specified)
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc

# Define the source files and object files
SRC = writer.c
OBJ = $(SRC:.c=.o)

# Define the output file
TARGET = writer

# Compiler flags
CFLAGS = -Wall -g

# Default target: build the application
all: $(TARGET)

# Rule to link the object files and generate the executable
$(TARGET): $(OBJ)
	$(LD) -o $@ $^

# Rule to compile the source code into object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target: remove generated files
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets (targets that don't correspond to files)
.PHONY: all clean
