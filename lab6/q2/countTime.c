#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // Threads
#include <time.h> // Time
#include <unistd.h> // Sleep
#define SIZE 4096

int N;
long int *counters = NULL; // A global array of N counters

void* workerFunc(void* arg);
void* monitorFunc(void* arg);

// Argc - counts the amount of words written in the prompt
// Argv - an array with said words
int main(int argc, char *argv[]) {
    // argv[0] - Program name
    // argv[1] - A int (N)

    // Checks to see if the user provided enough arguments (exactly 1 + name of program)
    if (argc != 2) {
        printf("\nError! You must have exactly 2 parameters.\n");
        exit(1);
    }

    int i;
    char inputBuffer[SIZE] = "";

    // We capture the integer from argv[1]
    if (sscanf(argv[1], "%d", &N) == 1 && N >= 0) {}

    // If capture fails
    else {
        // Prompts the user to try again
        printf("ERROR! Please input a positive integer: ");

        while (1) {
            // Gets user input
            if (fgets(inputBuffer, SIZE, stdin) != NULL)
                if (sscanf(inputBuffer, "%d", &N) == 1 && N >= 0)
                    break; // positive integer -> exit loop
            
            // Prompts the user to try again
            printf("ERROR! Please input a positive integer: ");
        }
    }

    // Allocate the global array after we get N
    counters = malloc(N * sizeof(long int));
    if (counters == NULL) {
        printf("\nERROR!: Malloc failed!\n");
        exit(1);
    }
    
    // Initialize all global counters to 0
    for (i = 0; i < N; i++)
        counters[i] = 0;

    pthread_t threads[N + 1]; // This stores the thread identifier

    // Fail check
    if (threads == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // We create N threads and send each one to increase their respective counter
    for (i = 0; i < N; i++) {
        // Pass the value i into the function workerFunc
        if (pthread_create(&threads[i], NULL, workerFunc, (void*)(long)i) != 0) {
            printf("Error creating thread %d\n", i + 1);
            exit(1);
        }
    }

    // We create the N + 1 thread that prints the counter results every 2 seconds
    if (pthread_create(&threads[N], NULL, monitorFunc, NULL) != 0) {
            printf("Error creating thread %d\n", N);
            exit(1);
        }

    // Wait for all threads to finish
    pthread_join(threads[N], NULL);

    
    // Release memory
    free(counters);

    return 0;
}

// This function increments a counter for thread associated with it
void* workerFunc(void* arg) {
    while (1)
        counters[(int)(long)arg]++;

    return NULL;
}

// This function monitors N strings and prints their respective counter
void* monitorFunc(void* arg) {
    
    // Initialize timers
    time_t start = time(NULL), curr;
    int duration = 20, i;

    do {
        // Wait 2 seconds
        sleep(2);

        // Print the counters
        printf("The counters are:\n[");
        for (i = 0; i < N; i++) {
            printf("%ld", counters[i]);

            if (i < N - 1)
                printf(", ");
            else
                printf("]\n\n");
        }
        curr = time(NULL);
    } while (curr - start < duration);
}