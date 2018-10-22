//Colin O'Neal
//User Dispatcher
//4-19-17
//$HOME/csc460/grading/dispatcher/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <time.h>

#define DEAD 9

int main(int argc, char *argv[])
{
	FILE *fopen(), *fp;
	int shmem, ptime;
	int *t, *user, *c;
	srand(time(NULL));
	int N, i, temp;
	int pid = getpid();
	int request;	
	int full, mutex, empty;
	int tt, avgtt;
	//Checks if argument has been made
	if(argc > 1)
		N = atoi(argv[1]);
	else
	{
		printf("Must enter number 0-50\n");
		return 0;
	}
	//When n is 0 should clear all data
	if(N == 0)
	{
		printf("Initializing Shutdown...\n");
		//Cleans up shared memory
                if ((shmctl(ptime, IPC_RMID, NULL)) == -1)
                        printf("ERROR removing shmem.\n");
                if ((shmctl(shmem, IPC_RMID, NULL)) == -1)
                        printf("ERROR removing shmem.\n");
		// Parent needs to clean up semaphores.
                if ((semctl(full, 0, IPC_RMID, 0)) == -1)
                        printf("%s", "Parent: ERROR in removing sem\n");
                if ((semctl(mutex, 0, IPC_RMID, 0)) == -1)
                        printf("%s", "Parent: ERROR in removing sem\n");
                if ((semctl(empty, 0, IPC_RMID, 0)) == -1)
                        printf("%s", "Parent: ERROR in removing sem\n");
		return 0;
	}
	else
	{
		//Gets the semaphores
		full = semget(IPC_PRIVATE, sizeof(int), 0777);
		mutex = semget(IPC_PRIVATE, sizeof(int), 0777);
		empty = semget(IPC_PRIVATE, sizeof(int), 0777);
		//Opens the file to read into
		if((fp = fopen("Dispatcher","r")) == NULL)
		{
			printf("Could not open Dispatcher");
		}
		//Initialize the semaphores
		semctl(full, 0, SETVAL, 0);
		semctl(empty, 0, SETVAL, 5);
		semctl(mutex, 0, SETVAL, 1);
		//Loop to fork
		for(i = 0; i < N; i++)
			if(fork() == 0)
				break;
		while(getpid() != pid)
		{
			think(t);
			printf("\t%d is thinking %d seconds\n",pid,clock);
			sleep(t);
			generate(c);
			printf("\t%d Requests %d",pid,c);
			think(t);
			fprintf(fp,"%d",pid);
			fprintf(fp,"%d",request);
			fprintf(fp,"%d",clock);
			p(mutex);
			sleep(request);
			v(mutex);
			temp = *t;
			tt = temp;
			avgtt += tt/i;
			printf("\t%d Finished in %d\n",pid,tt);
		}
		printf("\t%d is Logging off with an average TT of %d\n",pid,avgtt);
		printf("Cleaning up sems and shared mem...\n");
		sleep(1);
		//Cleans up shared memory
		if ((shmctl(ptime, IPC_RMID, NULL)) == -1)
    			printf("ERROR removing shmem.\n");
		if ((shmctl(shmem, IPC_RMID, NULL)) == -1)
    			printf("ERROR removing shmem.\n");
		// Parent needs to clean up semaphores.
    		if ((semctl(full, 0, IPC_RMID, 0)) == -1)
       			printf("%s", "Parent: ERROR in removing sem\n");
		if ((semctl(mutex, 0, IPC_RMID, 0)) == -1)
                        printf("%s", "Parent: ERROR in removing sem\n");
		if ((semctl(empty, 0, IPC_RMID, 0)) == -1)
                        printf("%s", "Parent: ERROR in removing sem\n");

		printf("All Done\n");
	}

	return 0;
}
//Makes time be random number for each user
think(int *t)
{
	*t = (rand()%(10-2)) + 2;
}
//Makes request be random for how long user needs to be in buffer
generate(int *c)
{
	*c = (rand()%(5-1)) + 1;
}
//Checks if queue is not full then will add into buffer if not
getQueue(int i, int *user, int front, int rear)
{
	if(rear >= 4)
	{
		rear = rear - 1;
	}
	else
		rear = rear + 1;
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

