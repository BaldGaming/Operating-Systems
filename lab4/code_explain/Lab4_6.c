#include <stdio.h>
#include<unistd.h>
void main(){
    int id, wid, status;
    printf("Here comes the date:\n");
    switch (  id =  fork() )  {  
         case -1:
              perror("fork");
              exit(1);
         case 0:
             execl("/bin/date", "date",NULL);
             perror("execl");
             exit(1);
          default:
             break;
     } /* switch */
     wid = wait(&status);
     printf("That was the date.\n");
} 
