#include <stdio.h>
#include<unistd.h>

void main(){
    printf("Here comes the date:\n");
    execl("/bin/date", "date", NULL);
    printf("ERROR - execl failed.\n");
}
