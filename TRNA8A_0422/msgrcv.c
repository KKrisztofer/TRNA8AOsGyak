#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MSGKEY 1234567

struct msgbuf1
{
	long tipus;
	char mtext[512];
} rcvbuf, *msgp;

struct msqid_ds ds, *buf;

int main()
{
	int msgid;
	key_t kulcs;
	int tipus, msgflg;
	int rtn, meret;
	
	kulcs = MSGKEY;
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);    
 	if ( msgid == -1)
    {
        perror("A rendszerhívás sikertelen!");
        exit(-1);
    }
	printf("Az üzenet ID: %d\n",msgid);

	msgp = &rcvbuf;
	buf = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buf);
	printf("Az üzenetek száma: %ld\n",buf->msg_qnum);
	
	while (buf->msg_qnum)
    {
    	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	    printf("Visszatérés: %d, Az üzenet:%s\n",rtn, msgp->mtext);
	    rtn = msgctl(msgid,IPC_STAT,buf);  
    }
	exit (0);
}
