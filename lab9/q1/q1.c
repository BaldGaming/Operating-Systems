#include <pthread.h>
#include <semaphore.h> // for semaphores
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define K 5
#define N 10

sem_t sem;
int stk[N];

void stkPush(int num);
int stkPop();

int main(int argc, char *argv[]){
    pthread_t tArr[K];
    int i = 0, ans[K];

    for (i = 0; i < K; i++)
        ans[i] = pthread_create(&tArr[i], NULL, tFunc, NULL);

    sleep(10);

    return 0;
}

void *tFunc(void *p)
{
    int num;

    while (1)
    {
        num = and() % 100;
        if (rand() % 2)
            stkPush(num);
        else
            stkPop();
    }

    sleep(1);
}

void *produce()
{
    while (1)
    {
        sleep(2);
        printf("Produced A\n");
        sem_post(&sem);
    }
}