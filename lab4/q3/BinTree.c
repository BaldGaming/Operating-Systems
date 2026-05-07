#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //for fork(), exec(), pid_t
#include <sys/wait.h> //for wait()

//argc - counts the amount of words written in the prompt
//argv - an array with said words
int main(int argc, char *argv[]) {
    //argv[0] - program name
    //argv[1] - mDepth - the depth of the binary tree
    //checks to see if the user provided enough arguments (exactly 1 + program name)
    if(argc != 2) {
        printf("ERROR\n");
        exit(1);
    }

    int mDepth = atoi(argv[1]); //gets the maximum depth number from the argument array of the binary tree
    int currDepth = 1; //current depth of this process in the tree
    //isChild flag - 1 if this process is a child, 0 if it is the parent
    //rightChild stores the second fork result, pid stores process ID's
    int isChild = 0, rightChild, pid;

    if(mDepth <= 0) {
        printf("Invalid depth\n");
        exit(1);
    }

    pid = getpid(); //gets the first parent pid
    printf("Parent PID: %d\n", pid);

    //continue creating children until reaching the required tree depth
    while(currDepth < mDepth) {
        isChild = 0;
        pid = fork(); //creates the left child
        
        //child process created by the first fork
        if(pid == 0) {
            printf("Left child: process PID: %d, Parent PID: %d\n", getpid(), getppid());
            currDepth++;
            isChild = 1; //marks this process as a child so it continues creating its subtree
        }
        //parent process creats the right child
        else if(pid > 0) {
            rightChild = fork(); //creates the right child
            
            if(rightChild == 0) { //child process created by the second fork
                printf("Right child: process PID: %d, Parent PID: %d\n", getpid(), getppid());
                currDepth++;
                isChild = 1;
            }
            if(rightChild == -1) {
                perror("error fork command\n");
                exit(1);
            }
        }
        else {
            perror("error fork command\n");
            exit(1);
        }
        
        //only the original parent of this level waits for its two children
        //child process continue the loop to create the next levels
        if(isChild == 0) {
            wait(NULL);
            wait(NULL);
            break;
        }
    }
    return 0;
}