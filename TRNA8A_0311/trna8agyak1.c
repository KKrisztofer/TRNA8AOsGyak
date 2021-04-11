#include <stdio.h>
#include <stdlib.h>
int main()
{
    int status;
    if((status = system("date"))<0){
        error("system() error");
    }
    if(WIFEXITED(status)){
        printf("Visszatérési érték: %d", WEXITSTATUS(status));
    }
    exit(0);
}
