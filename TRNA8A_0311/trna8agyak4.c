#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    if ((pid = fork()) == -1)
    {
        perror("error");
    }
    else if (pid == 0)
    {
        execl("/bin/ls", "ls", "-la", NULL);
        printf("Execlp error");
    }
    else
    {
        waitpid(pid,0,0);
        printf("Már nem fut a gyermek processz");
    }
    return 0;
}
