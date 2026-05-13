#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // Threads
#include <unistd.h> // Sleep
#define N 10

// Global counter and flag
int arr[N];
int foundFlag = 0;

void* findNum(void* arg);

int main(int argc, char *argv[]) {

    // Checks to see if the user provided enough arguments
    if (argc != 1) {
        printf("\nError! You must have exactly 1 parameter.\n");
        exit(1);
    }

    // We seed the random generator
    srand(time(NULL));

    int i, num;
    char input_buf[100];
    pthread_t threadId1, threadId2; // This stores the thread identifier

    // Fills the array
    for (i = 0; i < N; i++)
        arr[i] = rand() % 101; // Random number between 0 and 100

    // Prompt the user
    printf("\nEnter a number between 0 and 100: ");
    
    while(1) {
        if (fgets(input_buf, sizeof(input_buf), stdin) == NULL)
            exit(1);
        
        // Convert string to int using sscanf
        if (sscanf(input_buf, "%d", &num) != 1) {
        printf("ERROR! That is not a number. Try again: ");
        continue;
        }

        if (num < 0 || num > 100) {
            printf("ERROR! Input must be between 0 and 100, try again: ");
            continue;
        }

        break;
    }
    
    // We use an array to house the data that's being sent to the helper func
    // args[0] = num, args[1] = half_flag
    int args1[2] = {num, 0}; 
    int args2[2] = {num, 1};

    pthread_create(&threadId1, NULL, findNum, (void*)args1);
    pthread_create(&threadId2, NULL, findNum, (void*)args2);

    // Wait for threads to finish
    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);

    printf(foundFlag ? "%d is not in the array.\n" :
                       "%d is in the array.\n", num);

    return 0;
}

// Function for finding num
void* findNum(void* arg) {
    // Cast the pointer back into an array
    int *data = (int*)arg;

    int num = data[0];
    int half = data[1];
    int i = 0;

    if (foundFlag == 0) {
        if (half) {
            for (i = N/2; i < N; i++)
                if (arr[i] == num)
                    foundFlag = 1;
        }

        else {
            for (i = 0; i < N/2; i++)
                if (arr[i] == num)
                    foundFlag = 1;
        }
    }

    return NULL;
}