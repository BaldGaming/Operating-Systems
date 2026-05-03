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
        printf("\nError! You must have exactly 1 parameters.\n");
        exit(1);
    }

    char input[SIZE] = "";

    // A continuous loop so long as the user input isn't 'q'.
    while(1) {
        // Gets user input
        printf("$");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("scanf failed!\n");
            exit(1);
        }
        
        // Gets rid of the '\n' that is created by pressing enter.
        input[strcspn(input, "\n")] = '\0';

        // Stop condition
        if (strcmp(input, "q") == 0)
            break;

        // Initializes a new process and checks for errors
        int pid = fork();
        
        if (pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            exit(1);
        }

        // Child process 
        if (pid == 0) {
            if (execlp(input, input, NULL) == -1)
                printf("ERROR\n");
                exit(1); // Kills the child process if fork() fails.
        }
        
        // Parent process isn't supposed to do anything
        else wait(NULL);
    }

    printf("END\n");
    return 0;
}