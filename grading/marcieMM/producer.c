//Colin O'Neal
//4-28-17
//Producer
//$HOME/csc460/grading/marcieMM

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <time.h>

int main(int argc, char* argv[])
{
	FILE *fopen(), *fp;
	int row, col;
	int shmem;
	int pid = getpid();
	//Opens the file to read into
	if((fp = fopen("Memory","r")) == NULL)
	{
		printf("Could not open Memory");
	}
	/*****  Get Shared Memory and ID *****/
	row  =  shmget(IPC_PRIVATE, sizeof(int), 0777);
	col = shmget(IPC_PRIVATE, sizeof(int), 0777);
	if(argc < 3)
	{
		printf("Not valid argument.\n");
		exit(1);
	}
	int size = atoi(argv[1]);
	int time = atoi(argv[2]);
	if(size < 1 || size > (row*col))
	{
		printf("Not valid.\n");
		exit(1);
	}
	else if(time < 1 || time > 30)
	{
		printf("Not valid.\n");
		exit(1);
	}
	else
	{
		printf("PID: %d finished request of %d blocks and %d seconds.\n", pid,size,time);
	}
	
	return 0;
}

p(int s,int sem_id)
{
struct sembuf sops;

sops.sem_num = s;
sops.sem_op = -1;
sops.sem_flg = 0;
if((semop(sem_id, &sops, 1)) == -1) printf("%s", "'P' error\n");
}

v(int s, int sem_id)
{
struct sembuf sops;

sops.sem_num = s;
sops.sem_op = 1;
sops.sem_flg = 0;
if((semop(sem_id, &sops, 1)) == -1) printf("%s","'V' error\n");
}
