#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MSGKEY 654321L



struct msgbuf1 {		
	long mtype;
	char mtext[512];
} sndbuf, *msgp;

struct msqid_ds ds, *buf;

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

	msgp = &sndbuf;
	msgp->mtype = 1;
 	strcpy(msgp->mtext,"Hello1");
	msgsz = strlen(msgp->mtext) + 1;

    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);

	strcpy(msgp->mtext,"Hello2");
	msgsz = strlen(msgp->mtext) + 1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
    
    if (msgp->mtext == "exit")
    {
        exit(0);
    }

	key_t kulcs;
	int tipus;
	int meret;
	
	kulcs = MSGKEY;
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);    
 	if ( msgid == -1)
    {
        perror("\nA rendszerhívás sikertelen!");
        exit(-1);
    }
	printf("Az üzenet ID: %d",msgid);

	msgp = &sndbuf;
	buf = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buf);
	
	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	rtn = msgctl(msgid,IPC_STAT,buf);  

do {
    printf("\nMenü: ");
    printf("\n1. Üzenet darabszámának lekérdezése");
    printf("\n2. 1 üzenet kiolvasása");
    printf("\n3. Üzenetsor megszüntetése");
    printf("\n4. Kilépés\n");
    scanf("%d", &msgid);
  }while(msgid < 0 && msgid > 1);

  switch(msgid)
  {
    case 1:
        printf("\nAz üzenetek száma: %ld\n",buf->msg_qnum);
        break;

    case 2:
        printf("\nAz üzenet: %s\n", msgp->mtext);
        break;

    case 3:
        rtn = msgctl(msgid, IPC_RMID, NULL);
        printf("\nMegszüntetve\n");
        break;
    case 4:
        exit(0);      
  }
}
