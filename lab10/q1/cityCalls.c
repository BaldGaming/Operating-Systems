#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h> // for time()

#define K 4

sem_t mutex_prio, semArr[K];

void Calls(int City1, int City2);
void *Func(void *p);
void print(int City1, int City2);

int main(int argc, char *argv[])
{
    pthread_t tSec[K];
    int i, index[K];

    // Initialize the semaphores
    sem_init(&mutex_prio, 0, 1);
    for (i = 0; i < K; i++)
        sem_init(&semArr[i], 0, 1);

    // Tell each thread to go do shit
    for (i = 0; i < K; i++)
    {
        index[i] = i;
        pthread_create(&tSec[i], NULL, Func, &index[i]);
    }

    sleep(20);

    // Kill le epic semaphores
    sem_destroy(&mutex_prio);
    for (i = 0; i < K; i++)
        sem_destroy(&semArr[i]);

    return 0;
}

// Generates a random number between 0 and 3
void *Func(void *p)
{
    // Seed the random number generator with the current system time
    srand(time(NULL));
    // We cast "p" into a number to then represent the city that's calling
    int cityToCall, callingCity = *(int *)p;

    while (1)
    {
        // This do-while guarentees that "cityToCall" differs from "callingCity"
        do
        {
            cityToCall = rand() % 4;
        } while (callingCity == cityToCall);

        // We call "Calls" to then handle semaphores and the converstations with each secretary
        Calls(callingCity, cityToCall);
    }
}

void Calls(int City1, int City2)
{
    // Ensure we lock the lower ID first to prevent circular deadlocks
    int first = (City1 < City2) ? City1 : City2;
    int second = (City1 > City2) ? City1 : City2;

    int isHighPrioCall = (first == 2 && second == 3);
    int isLowPrioCall = (first == 0 && second == 1);

    // Priority Logic:
    if (isHighPrioCall)
        // High priority claims the priority mutex for the entire duration of the call
        sem_wait(&mutex_prio);

    else if (isLowPrioCall)
    {
        // Low priority must wait if high priority is holding the mutex.
        // If free, it immediately posts it so it doesn't block high priority from starting.
        sem_wait(&mutex_prio);
        sem_post(&mutex_prio);
    }
    
    // Critical Section, where we kock the secretaries
    sem_wait(&semArr[first]);
    sem_wait(&semArr[second]);

    print(City1, City2);

    // Release the secretaries
    sem_post(&semArr[second]);
    sem_post(&semArr[first]);

    // Release Priority Lock
    if (isHighPrioCall)
        sem_post(&mutex_prio);
}

void print(int City1, int City2)
{
    printf("%d started to talk with %d\n", City1, City2);
    sleep(1);
    printf("%d finished to talk with %d\n", City1, City2);
}