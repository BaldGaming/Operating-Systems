#include <stdio.h>
#include<unistd.h>

void main(){
    printf("Here comes the date:\n");
    fork();
    execl("/bin/date", "date", NULL);
    printf("That was the date.\n");
}
