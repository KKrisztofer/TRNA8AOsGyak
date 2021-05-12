#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#define SHMKEY 13

int main()
{
  int shmid;
  key_t key;
  int size = 512;
  int flag;

  key = SHMKEY;
  flag = 0;
  if((shmid = shmget(key, size, flag)) < 0)
  {
     flag = 00666 | IPC_CREAT;
     if((shmid = shmget(key, size, flag)) < 0)
     {
    perror("\nSikertelen!\n");
    exit(-1);
     }
  }
  printf("Azonosító: %d\n", shmid);
  return 0;
}
