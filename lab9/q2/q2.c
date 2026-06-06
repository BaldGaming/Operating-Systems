#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define N 100

sem_t board, exit, wait;

void passenger(int id);
void TAXI(int time);

int main(int argc, char *argv[])
{
    pthread_t tArr[N], tTaxi;
    int i, ans[N];

    sem_init(&board, 0, 0);
    sem_init(&exit, 0, 0);
    sem_init(&wait, 0, 0);

    // We create N threads and tell them to line up students for the taxi
    for (i = 0; i < N; i++)
        ans[i] = pthread_create(&tArr[i], NULL, passenger, (void*)i);

    // We create a thread that manages the taxi
    pthread_create(&tTaxi, NULL, TAXI, NULL);

    sleep(60);

    // Kill le epic semaphores
    sem_destroy(&board);
    sem_destroy(&exit);
    sem_destroy(&wait);

    return 0;
}

void passenger(int id)
{
    sem_wait(&wait); // wait until the taxi allows for students to board
    printf("")
    for (int i = 0; i < 4; i ++) {
        sem_post(&board); // let 4 students board
        
    }
}

void TAXI(int time)
{
    sem_post(&wait);
}