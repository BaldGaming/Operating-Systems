#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void main(){
	int id;
	printf("PID Before fork: %d\n", getpid());
	if((id=fork())==0){
		printf("After fork:\n");
		printf("PID is %d and ID is %d.\n", getpid(), id);
		execv("/home/braude/Documents/My/Hello.out", NULL);
		printf("Child's exit.\n");
	}
	else{
		printf("After fork:\n");
		printf("PID is %d and ID is %d.\n", getpid(), id);
		printf("Parent's exit.\n");
	}
}
