#!/bin/bash

# Check if both arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Two arguments are required. Usage: finder.sh <directory_path> <search_string>"
    exit 1
fi

filesdir=$1
searchstr=$2

# Check if filesdir is a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a directory."
    exit 1
fi

# Count the number of files in the directory and subdirectories
file_count=$(find "$filesdir" -type f | wc -l)

# Count the number of matching lines with searchstr
matching_lines_count=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

# Output the results
echo "The number of files are $file_count and the number of matching lines are $matching_lines_count"
