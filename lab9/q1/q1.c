#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define K 5
#define N 10

sem_t mutex, empty, full;
int stk[N], shmindex = 0;

void *tFunc(void *p);
void stkPush(int num);
int stkPop();

int main(int argc, char *argv[])
{
    pthread_t tArr[K];
    int i, ans[K];

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    for (i = 0; i < K; i++)
        ans[i] = pthread_create(&tArr[i], NULL, tFunc, NULL);

    sleep(10);

    // Kill le epic semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

// Generates a random number and preforms a push / pop based on the result
void *tFunc(void *p)
{
    int num;
    while (1)
    {
        num = rand() % 100;
        if (rand() % 2)
            stkPush(num);
        else
            stkPop();
        sleep(1);
    }
}

// This function pushes a num into a stack
void stkPush(int num)
{
    sem_wait(&empty);
    sem_wait(&mutex);

    // Update the stack and notify user
    stk[shmindex] = num;
    printf("PUSH %d\n", num);
    shmindex++;

    sem_post(&mutex);
    sem_post(&full);
}

// This function pops a num out of stack
int stkPop()
{
    int popped;

    sem_wait(&full);
    sem_wait(&mutex);

    // Update the stack and notify user
    shmindex--;
    popped = stk[shmindex];
    printf("POP %d\n", popped);

    sem_post(&mutex);
    sem_post(&empty);

    return popped;
}