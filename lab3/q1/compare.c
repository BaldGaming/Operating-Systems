#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 100
// Argc - counts the amount of words written in the prompt
// Argv - an array with said words
int main(int argc, char *argv[]) {
    // argv[0] - Program name
    // argv[1, 2] - the first and second file

    // Checks to see if the user provided enough arguments (exactly 3)
    if (argc != 3) {
        printf("\nError! You must have exactly 3 parameters.\n");
        exit(1);
    }

    // Define two character buffers
    char buffer1[SIZE];
    char buffer2[SIZE];

    // Opens said files and define variables
    int file1 = open(argv[1], O_RDONLY);
    int file2 = open(argv[2], O_RDONLY);
    int bytesRead1, bytesRead2, output, flag = 1;

    // Checks if the files actually opened
    if (file1 == -1 || file2 == -1) {
        perror("\nError! Either one of the files failed to open.\n");
        exit(1);
    }

    // Loops until we reach the end of either file
    while(1) {
        // We put the SIZE-bytes into buffer1 and 2 from their respective files.
        // byteRead holds the amount of bytes.
        bytesRead1 = read(file1, buffer1, SIZE);
        bytesRead2 = read(file2, buffer2, SIZE);

        // Check if there's an error
        if (bytesRead1 < 0 || bytesRead2 < 0) {
            perror("Two files read error");
            exit(1);
        }

        // Check is there's a difference: first, by comparing the amount of bytes, then their content.
        if (bytesRead1 != bytesRead2 || memcmp(buffer1, buffer2, bytesRead1) != 0) {
            flag = 0;
            break;
        }

        if (bytesRead1 == 0) break; // Exit condition
    }

    // Identical files
    if (flag)
        printf("Identical files\n");

    else {
        printf("Different files\n");

        // Creates a new output file. O_CREAT makes the file, O_TRUNC clears it if it exists
        output = open("compare.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

        // Check if there's an error
        if (output < 0) {
            perror("Output read error");
            exit(1);
        }

        // Rewind the curser back to the start of the files.
        lseek(file1, 0, SEEK_SET);
        lseek(file2, 0, SEEK_SET);

        // Fill the output file with the content of the original files
        while ((bytesRead1 = read(file1, buffer1, SIZE)) > 0) {
            write(output, buffer1, bytesRead1);
        }

        write(output, "\n", 1);

        while ((bytesRead2 = read(file2, buffer2, SIZE)) > 0) {
            write(output, buffer2, bytesRead2);
        }
        
        write(output, "\n", 1);

        close(output);
    }
    

    close(file1); close(file2);
    return 0;
}