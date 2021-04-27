#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarmk(int sig);

int main(int argc, char **argv)
{
    pid_t pid = (pid_t)atoi(argv[1]);
    kill(pid, SIGALRM);

    if (signal(SIGALRM, alarmk) == SIG_ERR)
    {
        printf("\"SIGALRM\" sikertelen!\n");
        return 1;
    }

    pause();
    return 0;
}

void alarmk(int sig)
{
    printf("TRNA8A\n");
    exit(1);
}
