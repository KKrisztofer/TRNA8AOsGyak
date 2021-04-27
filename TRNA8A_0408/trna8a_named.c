#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int main(){

    int fd;
    pid_t gyerek;

    if((mkfifo("TRNA8A", S_IRUSR | S_IWUSR)) < 0)
	{
        printf("Sikertelen\n");
        exit(1);
	}

    if((gyerek = fork()) < 0){
        printf("Sikertelen\n");
        exit(1);
    }
    if(!gyerek){
        char *szoveg = "Kerekes Krisztofer";

        if((fd = open("TRNA8A", O_WRONLY)) < 0){
            printf("Sikertelen\n");
            exit(1);
        }
        else 
        {
            write(fd, szoveg, strlen(szoveg));
        }
    }

    if(gyerek){
        char szoveg_sz[256];
        if((fd = open("TRNA8A", O_RDONLY)) <0 ){
            printf("Sikertelen\n");
            exit(1);

        }
        else
        {
            read(fd, szoveg_sz, sizeof(szoveg_sz));
            printf("Szoveg: %s.\n\n", szoveg_sz);
        }
        if((unlink("TRNA8A")) < 0 || (close(fd)) < 0)
        {
            printf("Sikertelen\n");
        }
	}

    return 0;

}
