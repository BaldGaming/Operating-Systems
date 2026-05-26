#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // Threads
#include <time.h> // Time
#define N 10
#define M 30

// Global matrix and result array
int matrix[N][M];
long rowSums[N];

void* fillRow(void* arg);
void* sumRow(void* arg);
void printMatrix();


int main(int argc, char *argv[]) {

    // Checks to see if the user provided enough arguments
    if (argc != 1) {
        printf("\nError! You must have exactly 1 parameter.\n");
        exit(1);
    }

    // We seed the random generator
    srand(time(NULL));

    int i;
    long sum = 0;
    pthread_t threads[N]; // This stores the thread identifier
    
    // We create N threads, one for each row
    for (i = 0; i < N; i++) {
        // We pass the index directly by casting it to void*
        if (pthread_create(&threads[i], NULL, fillRow, (void*)(long)i) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    // We wait for all threads to finish
    for (i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    // Print the matrix
    printMatrix();

    // We create another N threads for summing
    for (i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, sumRow, (void*)(long)i);

    // We join and accumulate the global results
    for (i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
        sum += rowSums[i];
    }

    printf("\nTotal sum of all elements is: %ld\n", sum);

    return 0;
}

// Each thread fills one specific row
void* fillRow(void* arg) {
    int row = (int)(long)arg; // Cast the value back to an int
    int j;

    for (j = 0; j < M; j++)
        matrix[row][j] = rand() % 101; // Random number between 0 and 100

    return NULL;
}

// Sums rows into a global array
void* sumRow(void* arg) {
    int row = (int)(long)arg;
    int j;
    
    rowSums[row] = 0; // Initialize global slot for this row

    for (j = 0; j < M; j++)
        rowSums[row] += matrix[row][j];
        
    return NULL;
}

// Prints the matrix
void printMatrix() {
    int i, j;

    for (i = 0; i < N; i++) {
        printf("[");
        
        for (j = 0; j < M; j++) {
            printf("%3d", matrix[i][j]);

            if (j < M - 1)
                printf(", ");
        }
        printf("]\n");
    }
}