#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MSGKEY 1234567

int main()
{
	int msgid, msgflg,  rtn;
	key_t kulcs;
	kulcs = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget(kulcs, msgflg);
	
	rtn = msgctl(msgid, IPC_RMID, NULL);	
	printf ("Vissztért: %d\n", rtn);

	exit (0);
}
