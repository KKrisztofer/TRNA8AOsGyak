#include <stdio.h>
#include <stdlib.h>

int main()
{
    int child;
    if((child=fork())<0)
    {
        perror("fork error");
    }
    else if(child==0)
    {
        if(execl("./child.out", "child", (char*) NULL) < 0)
        {
            perror("execl error");
        }
    }
    return 0;
}
