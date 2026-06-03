#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
#include <unistd.h>

sem_t semA, semB, semC;

void* A(void*) {
    while(1) {
        sem_wait(&semA);
        sem_wait(&semA);
        printf("A\n");
        sem_post(&semB);
        sleep(2);
    }
}

void* B(void*) {
    while(1) {
        sem_wait(&semB);
        printf("B\n");
        sem_post(&semC);
        sem_post(&semC);
    }
}

void* C(void*) {
    while(1) {
        sem_wait(&semC);
        printf("C\n");
        sem_post(&semA);
    }
}

int main (){
    // Initialize 3 threads and 3 semaphores
    pthread_t thread1, thread2, thread3;
    sem_init(&semA, 0, 2);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);
    
    // Tell each thread to activate a different function
    pthread_create(&thread1, NULL, A, NULL);
    pthread_create(&thread2, NULL, B, NULL);
    pthread_create(&thread3, NULL, C, NULL);

    // wait 5 seconds
    sleep(5);

    // Kill the semaphores
    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);

    return 0;
}