#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // For fork(), exec(), pid_t
#include <sys/wait.h>  // For wait()
#define SIZE 500

// Argc - counts the amount of words written in the prompt
// Argv - an array with said words
int main(int argc, char *argv[]) {
    // argv[0] - Program name

    // Checks to see if the user provided enough arguments (exactly 1)
    if (argc != 1) {
        printf("\nError! This program does not accept additional arguments.\n");
        exit(1);
    }

    char input[SIZE] = "";
    char path[SIZE + 8];

    printf("Welcome to LibShell!\n"
        "Enter <reader> for reading room commands\n"
        "Enter <catalog> for catalog search\n"
        "Enter <archive> for file archive tools");

    while(1) {
        // Gets user input
        printf("\nLib$** ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets failed!\n");
            exit(1);
        }
        
        // Gets rid of the '\n' that is created by pressing enter.
        input[strcspn(input, "\n")] = '\0';

        // Stop condition
        if (strcmp(input, "exit") == 0)
            break;

        // Initializes a new process and checks for errors
        int pid = fork();
        
        if (pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            exit(1);
        }

        // We build a path string: "./" + input + "_shell"
        snprintf(path, sizeof(path), "./%s_shell", input);

        // Child process
        if (pid == 0) {
            if (strcmp(input, "reader") == 0) {
                printf("Entering Reader Shell...\n");
            }
            else if (strcmp(input, "catalog") == 0) {
                printf("Entering Catalog Shell...\n");
            }
            else if (strcmp(input, "archive") == 0) {
                printf("Entering Archive Shell...\n");
            }
            else {
                printf("Not Supported\n");
                exit(1); 
            }
            execlp(path, path, NULL);
        }
        
        // Parent process isn't supposed to do anything
        else wait(NULL);
    }

    printf("\nGoodbye from LibShell\n");
    return 0;

}