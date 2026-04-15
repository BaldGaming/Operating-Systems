#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Argc - counts the amount of words written in the prompt
// Argv - an array with said words
int main(int argc, char *argv[]) {
    // argv[0] - Program name
    // argv[1] - A file

    // Checks to see if the user provided 2 arguments
    if (argc != 2) {
        printf("Error! You must have exactly 2 parameters.\n");
        exit(1);
    }

    // Opens the given file and defines a string
    int file = open(argv[1], O_RDWR | O_APPEND);
    int size;
    char word[] = "END";

    // Checks if the file opens
    if (file != -1) {

        // Gets the size (in bytes) of the file
        size = lseek(file, 0, SEEK_END);

        // Adds a new line if the file is empty
        if (size > 0)
            write(file, "\n", 1);

        write(file, word, strlen(word));
        printf("Wrote %s successfully!\n", word);
        close(file);
    }

    else {
        // Checks the file exists
        file = open(argv[1], O_WRONLY | O_CREAT, 0644);

        // Check if there's an error
        if (file == -1) {
            perror("Error! Failed to create file\n");
            exit(1);
        }

        write(file, word, strlen(word));
        printf("Created %s and wrote %s successfully!\n", argv[1], word);
        close(file);
    }

    return 0;
}