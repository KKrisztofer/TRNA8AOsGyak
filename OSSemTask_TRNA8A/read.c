#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 67L
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

    /* A write.c keszitett osztott szegmenst. */
	shmflg = 0;

	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("A rendszerhívás sikertelen!\n");
	    exit(-1);
	}

    /* Kapcsolodas */

	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);
	if (segm == (void *)-1) {
		perror("Sikertelen kapcsolódás!\n");
		exit(-1);
	}

    /* A szoveg kiiratasa. */
	if (strlen(segm->szoveg) > 0) 
    {
		printf("A szoveg: %s\n",segm->szoveg);
    }
	int rtn = shmctl(shmid, IPC_RMID, NULL);
	printf("Szegmens torolve. Hibakod: %d\n", rtn);
	return 0;
}
