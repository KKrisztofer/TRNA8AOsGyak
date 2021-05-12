#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 13
#include <string.h>

struct str {
    int lng;
    char text[512-sizeof(int)];
} *segment;

int main()
{
    int shmid, flag, rtn, choose;
    int size = 512;
    key_t key;

    key = SHMKEY;
    flag = 0;

    if((shmid = shmget(key, size, flag)) < 0)
    {
        flag = 00666 | IPC_CREAT;
        if((shmid = shmget(key, size, flag)) < 0)
        {
            perror("Sikertelen shmget!\n");
            return -1;
        }
    }

    printf("Az azonosító : %d\n", shmid);

    flag = 00666 | SHM_RND;
    segment = (struct str *)shmat(shmid, NULL, flag);

    if(segment == (void *) - 1)
    {
        perror("Sikertelen csatlakozas\n");
        return -1;
    }

    if(strlen(segment->text) > 0)
    {
        printf("A szöveg a memóriában: %s\n", segment->text);
    }
    
    printf("Add meg az új szöveget: ");
    scanf("%s", segment->text);
    printf("\nAz új szöveg: %s\n", segment->text);

    shmdt(segment);
    struct shmid_ds shmid_ds, *buf;
    buf = &shmid_ds;
    flag = 0;

    do
    {
        printf("Menü:\n");
        printf("1. státusz lekérése\n");
        printf("2. szegmens törlése\n");
        scanf("%d", &choose);

    }while(choose != 0 && choose != 1);

    switch(choose){
        case 1:
            rtn = shmctl(shmid, IPC_STAT, buf);
            printf("Méret: %ld\n", buf->shm_segsz);
            printf("PID: %d\n", buf->shm_lpid);
            break;
        case 2:
            rtn = shmctl(shmid, IPC_RMID, NULL);
            printf("Szegmens megszüntetve!\n");
            break;
    }

    return 0;
}
