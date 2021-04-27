#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void semmi();

int main(){
    unsigned sec = 5;
    signal(SIGALRM, semmi);
    alarm(sec);

    printf("%d varok.\n",1);
    pause();

    printf("Megerkezett az alarm.\n");

	return 0;
}

void semmi(){ ; }