#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // Exit
#include <unistd.h>    // For fork(), exec(), pid_t
#include <sys/wait.h>  // For wait()
#include <pthread.h> // Threads

#define SIZE 4096

int nReturn = 0, mReturn = 0, N, M;

void* divisorsSum(void* arg);

// Argc - counts the amount of words written in the prompt
// Argv - an array with said words
int main(int argc, char *argv[]) {
    // argv[0] - Program name
    // argv[1] - An int (N)
    // argv[2] - An int (M)

    // Checks to see if the user provided enough arguments (exactly 2 + name of program)
    if (argc != 3) {
        printf("\nError! You must have exactly 3 parameters.\n");
        exit(1);
    }

    int i;
    char inputBuffer[SIZE] = "";

    // We capture the integer from argv[1]
    if (sscanf(argv[1], "%d", &N) == 1 && N >= 0 &&
        sscanf(argv[2], "%d", &M) == 1 && N >= 0) {}

    // If capture fails
    else {
        // Prompts the user to try again
        printf("ERROR! Please input two positive integers: ");

        while (1) {
            // Gets user input
            if (fgets(inputBuffer, SIZE, stdin) != NULL) {
                if (sscanf(inputBuffer, "%d %d", &N, &M) == 2 && N >= 0 && M >= 0)
                    break; // positive integer -> exit loop
            
            // Prompts the user to try again
            printf("ERROR! Please input two positive integers: ");
            }
        }
    }

    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, divisorsSum, &N) != 0 ||
        pthread_create(&thread2, NULL, divisorsSum, &M) != 0) {
        printf("Error creating threads\n");
        exit(1);
        }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    (nReturn == M && mReturn == N) ? printf("Amicable Numbers\n") : printf("Not Amicable Numbers\n");

    return 0;
}

// This function sums the divisors of any given positive integer
void* divisorsSum(void* arg) {
    int n = *(int*)arg;
    int sum = 0, i;

    // Divisor algorithm
    for (i = 1; i < n; i++)
        if (n % i == 0)
            sum += i;

    // Assign to the correct global variable depending on which number we processed
    if (n == N)
        nReturn = sum;
    else
        mReturn = sum;

    // Kill le epic child proccess
    return NULL;
}