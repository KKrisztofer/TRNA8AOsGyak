#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include<unistd.h>
#define SHMKEY 67L
#define KEY 41L
#define PERM 00666

int main()
{
	int shmid;		/* osztott memoria azonosito */
	key_t key;		/* shmem kulcs */
	int size=512;	/* osztott memoria merete */
	int shmflg;		/* flag */
    struct vmi {
		int  hossz;
		char szoveg[512-sizeof(int)]; /* az egesz merete 512, ezert a hossz valtozot levonjuk a tombbol */
	} *segm;
	key = SHMKEY;

	/* Megnezzuk, van-e mar SHMKEY kulcsu es "size" meretu szegmens. */
	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0)
    {
	    shmflg = 00666 | IPC_CREAT; /* Ha nincs, létrehozzuk. */
	    if ((shmid=shmget(key, size, shmflg)) < 0)
        {
	        exit(-1);   /* Sikertelen a rendszerhívás. */
	    }
	}

	printf("\nsmh id: %d \n", shmid);
	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);
	if (segm == (void *)-1)
    {
		perror("Sikertelen!\n");
		exit(-1);
	}

    int id; /* A szemafor azonosítója */
 
	if ((id = semget(KEY, 1, 0)) < 0) /* Ha még nem létezik. */
    {
		if ((id = semget(KEY, 1, PERM | IPC_CREAT)) < 0)
        {
			exit(-1); /* Sikertelen a rendszerhívás. */
		}
	}
	else
    {
		exit(0); /* Ha létezik a szemafor. */
	}

	if (semctl(id, 0, SETVAL, 1) < 0)
    {
		perror("Hiba! A szemafo nem jött létre.\n");
	}
	struct sembuf up[1]  =  {0,  1, SEM_UNDO};
    struct sembuf down[1] = {0, -1, SEM_UNDO};

	semop(id, down, 1);   /* A belépési szakasz */
	strcpy(segm->szoveg,"Hello vilag!");
	sleep(3);
	semop(id, up, 1);    /* Ez a kilépési szakasz */
	if (semctl(id, 0, IPC_RMID, 0) < 0)
    {
		perror("Sikertelen törlés.\n");
		exit(-1);
	}

	puts("A szemafor megszünt.\n");
	shmdt(segm);
	return 0;
}
	
	
