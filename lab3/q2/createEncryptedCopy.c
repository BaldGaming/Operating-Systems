#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

// Argc - counts the amount of words written in the prompt
// Argv - an array with said words
int main(int argc, char *argv[]) {
    // argv[0] - Program name
    // argv[1] - A file
    // argv[2] - Integer N
    // argv[3] - String STR

    // Checks to see if the user provided enough arguments (exactly 3)
    if (argc != 4) {
        printf("\nError! You must have exactly 4 parameters.\n");
        exit(1);
    }

    // Open the given file and define variable
    int file   = open(argv[1], O_RDONLY);
    int N = atoi(argv[2]);
    int output, bytesRead;

    // Define a character buffer the size of N
    char buffer[N];

    // Define a variable for the path
    char path[] = "encrypted/a.txt";

    // Checks if the file actually opened
    if (file == -1) {
        perror("\nError! The file failed to open.\n");
        exit(1);
    }

    // Checks if a folder already exists.
    if (opendir("encrypted") != NULL) {
        printf("\nFolder 'encrypted' already exists, creating file:\n");
    }
    else {
        if (mkdir("encrypted", 0777) == -1) {
            perror("\nError! Failed to create directory");
            exit(1);
        }
    }

    // Create the output file and checks for errors
    output = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output == -1) {
        perror("\nError! The file failed to be created.\n");
        exit(1);
    }

    // Loop until we hit the end of 'file'
    while(1) {
        // We put 2 bytes from 'file' into a buffer
        // byteRead holds the amount of bytes.
        bytesRead = read(file, buffer, N);

        // Check if there's an error
        if (bytesRead < 0) {
            perror("File read error");
            exit(1);
        }

        if (bytesRead == 0) break; // exit condition.

        // Write the characters we just read
        write(output, buffer, bytesRead);

        // Write the string if we successfully read a full block of N characters
        if (bytesRead == N) 
            write(output, argv[3], strlen(argv[3]));
    }

    printf("\nFinished task successfully!\n");

    close(file);
    close(output);
    return 0;
}