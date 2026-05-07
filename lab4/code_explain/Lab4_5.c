#include <stdio.h>
#include<unistd.h>

void main(){
    int id, wid, status;
    printf("Here comes the date:\n");
    if ( ( id =  fork() ) == 0 )  {  
       printf("PID is %d and ID is %d.\n", getpid(), id);
       execl("/bin/date", "date",NULL);
    }
    wid = wait(&status);
    printf("That was the date.\n");
    printf("PID is %d and ID is %d.\n", getpid(), id);
    printf("wid = %d and status = %d\n", wid, status);
}
