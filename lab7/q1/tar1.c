#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // Exit
#include <unistd.h>    // For fork(), exec(), pid_t
#include <sys/wait.h>  // For wait()

#define N 10

int main() {
    int c1, c2, t, i;
    c2 = 1; c1 = 0;
    
    for (i = 1; i < N; i++) {
        switch(fork()) {
            case -1: // Fork() failed
                printf("Error creating process\n");
                return -1;

            case 0: // Child process
                printf("%d ",c2);
                exit(0);


            default: // Parent process
                wait(NULL);
                t = c1 + c2;
                c1 = c2;
                c2 = t;
                break;
        }
    }
    printf("%d\n",c2);
    return 0;
}