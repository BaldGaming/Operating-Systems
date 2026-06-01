#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
sem_t semA, semB;

void* create_message ( void* str ){
    for (int i = 0; i < 10; i++) {
        sem_wait(&semA);
        printf ("I've wrote a message #%d. %s\n", i+1, (char*)str);
        sem_post(&semB);
    }
}
 
int main (){
    // We initialize a thread and 2 semaphores
    pthread_t thread; 
    sem_init(&semA, 0, 1);
    sem_init(&semB, 0, 0);

    // Tell the thread to go activate create_message
    pthread_create (&thread, NULL, create_message, (void*)"Thread A");
    
    for (int i = 0; i < 10; i++) {
        sem_wait(&semB);
        printf("The message #%d was printed. Thread B \n\n", i+1);
        sem_post(&semA);
    }

    pthread_join(thread, NULL);

    // Kill the semaphore
    sem_destroy(&semA);
    sem_destroy(&semB);
}