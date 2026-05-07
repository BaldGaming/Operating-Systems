#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // For fork(), exec(), pid_t
#include <sys/wait.h>  // For wait()


// Argc - counts the amount of words written in the prompt
// Argv - an array with said words
int main(int argc, char *argv[]) {
    // argv[0] - Program name
    // argv[1] - The program name we wish to run
    // argv[2] - The amount of times we want to execute said program

    // Checks to see if the user provided enough arguments (exactly 3)
    if (argc != 3) {
        printf("\nError! You must have exactly 3 parameters.\n");
        exit(1);
    }

    int N = atoi(argv[2]); // Gets the number from the argument array

    while (N > 0) {
        // Initializes a new process and checks for errors
        int pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            exit(1);
        }

        // Child process 
        if (pid == 0) {
            execl(argv[1], argv[1], NULL);

            // This runs only if there's an error
            perror("Exec failed");
            exit(1);
        }

        // Parent process isn't supposed to do anything
        else wait(NULL);

        N--;
    }

    printf("END\n");
    return 0;
}