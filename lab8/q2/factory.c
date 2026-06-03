#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
#include <unistd.h>

sem_t sem;

void* produce() {
    while(1) {
        sleep(2);
        printf("Produced A\n");
        sem_post(&sem);
    }
}

void* collect() {
    while(1) {
        sem_wait(&sem);
        sem_wait(&sem);
        printf("Collected AA\n");
    }
}
 
int main (){
    // Initialize
    pthread_t thread1, thread2;
    sem_init(&sem, 0, 0);

    // Create the thread
    pthread_create(&thread1, NULL, produce, NULL);
    pthread_create(&thread2, NULL, collect, NULL);

    // wait 20 seconds
    sleep(20);

    // Kill the semaphore
    sem_destroy(&sem);

    return 0;
}