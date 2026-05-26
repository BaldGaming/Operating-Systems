#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // Threads
#include <unistd.h> // Sleep


// Global counter
unsigned long int counter = 0;

void* countingFunc(void* arg);
void* print(void* arg);

int main(int argc, char *argv[]) {

    // Checks to see if the user provided enough arguments
    if (argc != 1) {
        printf("\nError! You must have exactly 1 parameter.\n");
        exit(1);
    }

    int i;
    pthread_t threadId; // This stores the thread identifier


    pthread_create(&threadId, NULL, countingFunc, NULL);

    for (i = 0; i < 10; i++)
        pthread_create(&threadId, NULL, print, NULL);

    sleep(2);

    return 0;
}

// This function counts the CPU speed indefinitely
void* countingFunc(void* arg) {
    while (1)
        counter++;
    return NULL;
}

// This function prints the result
void* print(void* arg) {
    printf("%lu\n", counter);

    return NULL;
}