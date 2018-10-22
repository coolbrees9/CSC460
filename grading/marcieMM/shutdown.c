//Colin O'Neal
//4-28-17
//Shutdown
//$HOME/csc460/grading/marcieMM

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main()
{
	FILE *fopen(), *fp;
	int shmem, semid;

	if((fp = fopen("Memory","r")) == NULL)
	{
		printf("Error: could not open file.");
	}

	//Cleans up shared memory
	if ((shmctl(shmem, IPC_RMID, NULL)) == -1)
    		printf("ERROR removing shmem.\n");
	// Parent needs to clean up semaphores.
   	if ((semctl(semid, 0, IPC_RMID, 0)) == -1)
    		printf("%s", "Parent: ERROR in removing sem.\n");

	printf("All Done\n");
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
