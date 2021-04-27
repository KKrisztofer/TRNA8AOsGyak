#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2];
    int gyerek;

    if (pipe(fd))
    {
        perror("cső hiba!\n");
        return 1;        
    }

    gyerek = fork();
    
    if (gyerek > 0)
    {
        char s[1024];
        close (fd[1]);
        read(fd[0], s, sizeof(s));
        printf ("%s", s);

        close(fd[0]);
    }
    else if (gyerek == 0)
    {
            close(fd[0]);
            write(fd[1], "Kerekes Krisztofer TRNA8A\n", 27);
            close(fd[1]);
    }
        
        return 0;
}
