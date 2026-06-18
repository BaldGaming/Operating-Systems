#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h> // for time()

#define K 20
#define N 10

sem_t semTablet, semTorque, semLine, mutexVip;

int main() {
    // We first print the opening statement with N and K's values
    printf("--- Institute Open (N=%d, K=%d) ---", N, K);

    // 5 threads - 3 for the Mechanics and 2 for Air
    pthread_t mech0, mech1, mech2, air0, air1;

    // Initialize the semaphores
    sem_init(&semTablet, 0, 2);
    sem_init(&semTorque, 0, 2);
    sem_init(&semLine, 0, 3);

}