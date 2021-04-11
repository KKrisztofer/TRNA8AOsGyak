#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid;
    int status;
    if ( (pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        exit(7);
    }
    if (WIFEXITED(status))
    {
        printf("Normális befejeződés, visszaadott érték = %d\n", WEXITSTATUS(status));
    }
    if ( (pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        abort();
    }
    if (wait(&status) != pid)
    {
        perror("wait error");
    }
    if (WIFSIGNALED(status))
    {
        printf("Nem normális befejeződés, szignál sorszmáma = %d\n", WTERMSIG(status));
    }
    return 0;
}
