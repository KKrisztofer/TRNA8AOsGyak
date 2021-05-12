#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MSGKEY 1234567

struct msgbuf1 {		
	long mtype;
	char mtext[512];
} sndbuf, *msgp;

int main()
{
	int msgid;
	key_t key;
	int msgflg;
	int rtn, msgsz;
	
	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflg);
 	if ( msgid == -1)
    {
        perror("\nA rendszerhívás sikertelen!");
        exit(-1);
    }
	printf("Az msgid %d, %x : ", msgid, msgid);

	msgp = &sndbuf;
	msgp->mtype = 1;   			
 	strcpy(msgp->mtext,"Hello1");
	msgsz = strlen(msgp->mtext) + 1;	

    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("\nAz üzenet: %s", msgp->mtext);

	strcpy(msgp->mtext,"Hello2");
	msgsz = strlen(msgp->mtext) + 1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("\nAz üzenet: %s \n", msgp->mtext);

	exit (0);
}
