#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // Exit
#include <unistd.h>    // For fork(), exec(), pid_t
#include <sys/wait.h>  // For wait()
#include <pthread.h> // Threads

#define SIZE 4096

int N, M;

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

    int i, sumN, sumM;
    char inputBuffer[SIZE] = "";

    // We capture the integer from argv[1]
    if (sscanf(argv[1], "%d", &N) == 1 && N >= 0 &&
        sscanf(argv[2], "%d", &M) == 1 && M >= 0) {}

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

    // We catch each res value created by the threads
    void *res1 = NULL;
    void *res2 = NULL;

    // We transfer the returned value into the variables we just defined
    pthread_join(thread1, &res1);
    pthread_join(thread2, &res2);

    // Safety check
    if (res1 == NULL || res2 == NULL) {
        printf("ERROR! Thread failed to calculate sum.\n");
        free(res1);
        free(res2);
        exit(1);
    }

    // Cast the void* back to int* and pull the values out
    sumN = *(int*)res1;
    sumM = *(int*)res2;

    // Print the result
    (sumN == M && sumM == N) ? printf("Amicable Numbers\n") : printf("Not Amicable Numbers\n");

    // Free the allocated memory
    free(res1);
    free(res2);

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
    int* res = malloc(sizeof(int));
    if (res == NULL)
        pthread_exit(NULL);

    *res = sum;

    return res;
}