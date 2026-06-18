#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 100

sem_t semFree, semDrive, semArrive, mutex;
// semFree - counts the number of free seats in the taxi.
// semDrive - allows the taxi to leave only when 4 students are inside.
// semArrive - blocks students until the taxi arrives at the college.
// mutex - protects shared variables cnt and turn.

int cnt = 0;
// cnt - counts how many students are currently inside the taxi.

void passenger(int id);
void TAXI(int time);
void *runPass(void *p);
void *runTaxi(void *p);

int main(int argc, char *argv[])
{
    if (argc != 1)
    { // checks that the only argument is the program name
        printf("ERROR\n");
        exit(1);
    }

    pthread_t tArr[N], tTaxi;
    int i = 0, t = 5, ids[N];

    // Initialize 4 semaphores
    sem_init(&semFree, 0, 4);   // Taxi starts with 4 empty seats.
    sem_init(&semDrive, 0, 0);  // Taxi cannot leave until it is full.
    sem_init(&semArrive, 0, 0); // Students wait until the taxi arrives.
    sem_init(&mutex, 0, 1);     // Protects cnt from being modified by multiple threads simultaneously.

    // Creats N threads
    pthread_create(&tTaxi, NULL, runTaxi, &t);
    for (i = 0; i < N; i++)
    {
        ids[i] = i + 1;
        pthread_create(&tArr[i], NULL, runPass, &ids[i]);
    }

    sleep(60);

    // Kill semaphores
    sem_destroy(&semFree);
    sem_destroy(&semDrive);
    sem_destroy(&semArrive);
    sem_destroy(&mutex);

    return 0;
}

// Simulates a student waiting for their turn, entering the taxi, and waiting until arrival.
void passenger(int id)
{
    sem_wait(&semFree); // Wait until a seat becomes available in the taxi.
    sem_wait(&mutex);   // Enter critical section.

    printf("Student #%d start\n", id);
    printf("Student #%d is in the TAXI\n", id);
    cnt++; // Update the number of students currently in the taxi.

    if (cnt == 4)
    { // Notify the taxi that it is full and can depart.
        sem_post(&semDrive);
    }

    sem_post(&mutex);     // Leave critical section.
    sem_wait(&semArrive); // Wait until the taxi arrives at the college.

    printf("Student #%d arrived. Out of TAXI\n", id);
}

// Simulates the taxi ride to college and back to the station. The taxi leaves only when 4 students are inside.
void TAXI(int time)
{
    sem_wait(&semDrive); // Wait until 4 students have entered the taxi.
    printf("Taxi Left Station\n");
    sleep(time); // Simulate taxi travel time.
    printf("Taxi Arrived\n");

    sem_wait(&mutex);
    cnt = 0;
    sem_post(&mutex);

    for (int i = 0; i < 4; i++)
    { // Allow all passengers to leave the taxi.
        sem_post(&semArrive);
    }

    sleep(time); // Simulate taxi travel time.

    for (int i = 0; i < 4; i++)
    { // Mark all taxi seats as available again.
        sem_post(&semFree);
    }
}

// Runs a single passenger thread.
void *runPass(void *p)
{
    passenger(*(int *)p);
}

// Runs the taxi thread continuously.
void *runTaxi(void *p)
{
    while (1)
    {
        TAXI(*(int *)p);
        sleep(1); // Simulates processing time between operations.
    }
}