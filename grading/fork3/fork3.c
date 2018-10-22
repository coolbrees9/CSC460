//Colin O'Neal
//CSC460
//2-13-17
//Shared Sequencing
// Can be found on intruder in: $HOME/csc460/grading/fork3/fork3.c

#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define TURN shmem[0]

int main(int argc, char *argv[])
{
	int shmid;
	char *shmem;
	int i;
	int N;                  // Holds the number of procs to generate
	int myID = 0;           // used to identify procs in sync
	int LoopCount = 10;     // Times each proc will "speak"

/*****  Get the command line argument for how many procs. Default of 5 ****/
	if (argc < 2)
        	N = 5;
	else
        	N = atoi(argv[1]);      //  Not error testing here :(
	

/*****  Get Shared Memory and ID *****/

	shmid  =  shmget(IPC_PRIVATE, sizeof(char), 0770);
	if (shmid == -1)
    	{
    		printf("Could not get shared memory.\n");
    		return(0);
    	}

/****   Attach to the shared memory  ******/

	shmem = (char *) shmat(shmid, NULL, SHM_RND);



/****  Initialize the shared memory ****/
	TURN = 'A';

	if(26 < N || 1 > N)							//Checks to make sure you enter a number between 1 and 26
	{
		printf("Must be a number between 1 and 26!!! \n");
	}
	else
	{
		
		printf("You entered the number: %d\n",N);
		char id = 'A';
		char found = 'a';
		int count = 1;
		char otherId = 'B';
		if(N == 1)
			otherId = 'A';
		int  i, x;
		for( i = 1; i < N; i++)							//Runs while i is less than the number entered after a.out
		{
			x = fork();
			if(x > 0) break;

			id = otherId;
			otherId++;
			count++;
			if(count == N)							//When the number of children is greater than or equal to N then it will reset otherId to A
				otherId = 'A';
		}
		for(i = 0; i < 5; i++)							//Runs this to print 5 times
		{
			found = 'a';
     			while (found != id)
     			{
				found = TURN;
			}
     			printf("%c: %d\n",id,getpid());					//Print statement that prints it out in order
			TURN = otherId;
		}
	if (shmdt(shmem) == -1 ) printf("shmgm: ERROR in detaching.\n");		//Detaches and cleans up shared memory
		sleep(1);

	return 0;
	}
}
