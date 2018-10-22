//Colin O'Neal
//4-28-17
//Consumer
//$HOME/csc460/grading/marcieMM

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(int argc, char* argv[])
{
	FILE *fopen(), *fp;
	int row, col, buffer;
	int full, empty, mutex;
	if(argc < 4)
	{
		printf("Must have 4 arguments,\n");
		exit(1);
	}
	row = atoi(argv[1]);
	col = atoi(argv[2]);
	buffer = atoi(argv[3]);
	if(row < 1 || row > 20)
	{
		printf("Rows must be between 1 and 20.\n");
		exit(1);
	}
	else if(col < 1 || col > 50)
	{
		printf("Col must be between 1 and 50.\n");
		exit(1);
	}
	else if(buffer < 1 || buffer > 26)
	{
		printf("Buffer must be between 1 and 26.\n");
		exit(1);
	}
	else
	{
		if((fp = fopen("Memory","w")) == NULL)
    		{
    			printf("start:  could not open file.\n");
    			return(0);
    		}
		/*****  Give everyone permission to read file.  *****/
		system("chmod 755 Memory");
		//Asks for semaphores 
		full = semget(IPC_PRIVATE, sizeof(int), 0777);
		mutex = semget(IPC_PRIVATE, sizeof(int), 0777);
		empty = semget(IPC_PRIVATE, sizeof(int), 0777);
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
