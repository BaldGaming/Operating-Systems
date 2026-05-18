#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // Threads
#include <sys/time.h> // gettimeofday()
#define SIZE 4096

int curThread;

void* f(void* arg);

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

    int N, i;
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
    
    // This stores the thread identifier
    pthread_t threads[N];

    // Fail check
    if (threads == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // We create N threads
    for (i = 0; i < N; i++) {
        // Pass the value i + 1
        if (pthread_create(&threads[i], NULL, f, (void*)(long)(i + 1)) != 0) {
            printf("Error creating thread %d\n", i + 1);
            exit(1);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    return 0;
}

void* f(void* arg) {

    // Define the struct for time and a variable that holds the elapses time
    struct timeval start, curr;
    double elapsedTime;

    // Cast the received arg back into an int
    int threadNum = (int)(long)arg;

    // We get the starting time
    gettimeofday(&start, NULL);

    // Calculate the starting time
    while(1) {

        // We get the current time
        gettimeofday(&curr, NULL);

        if (curThread != threadNum) {
            elapsedTime = (curr.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
            elapsedTime += (curr.tv_usec - start.tv_usec) / 1000.0;   // us to ms

            printf("Time slice for thread %d = %lf ms.\n", threadNum, elapsedTime);

            // We update curThread and reset the clock
            curThread = threadNum; 
            start = curr;
        }
    }
    return NULL;
}