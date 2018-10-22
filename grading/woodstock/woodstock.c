//Colin O'Neal
//3-22-17
//Woodstock's Bank
//$HOME/csc460/grading/woodstock

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <math.h>

int main(int argc, char * argv[])
{
	int N, Balance = -1, mutex;
	FILE *fopen(), *fp;
	int i, HowManySems = 1;
	int loop = 16;
	int *Bal;

	if(argc > 1)
		N = atoi(argv[1]);

	if(argc <= 1)						//Checks to see if the args are just the file
	{
		if((fp = fopen("Balance","r")) == NULL)
		{
			/*****  Open File to hold Shared Memory ID  *****/

			if((fp = fopen("Balance","w")) == NULL)
    			{
    				printf("start:  could not open file.\n");
    				return(0);
    			}

			/*****  Give everyone permission to read file.  *****/
			system("chmod 755 Balance");

			Balance  =  shmget(IPC_PRIVATE, 4, 0777);
			if (Balance == -1)
    			{
    				printf("Could not get shared memory.\n");
    				fclose(fp);
    				return(0);
    			}
			Bal = (int*) shmat(Balance, NULL, SHM_RND);
			*Bal = 1000;

			mutex = semget(IPC_PRIVATE, HowManySems, 0777);
			//Initialize sems
			semctl(mutex, 0, SETVAL, 1);
			if(mutex == -1)
			{
				printf("%s", "Semget Failed. \n");
				return -1;
			}
			/*****  Write SHMID into file and close file.  *****/

			fprintf(fp,"%d\n",Balance);
			fprintf(fp,"%d\n",mutex);
			fclose(fp);

			/*****  PRINT MESSAGE AND TERMINATE  *****/

			printf("shared-Balance is %d\n",*Bal);
		}
		else
			printf("Shared Memory already setup\n");
	}
	else if(N >= 1 && N <= 100)				//Checks if the number 1-100 was entered in argv[1]
	{
		int role = 0, currValue;
		int myID = 0;
		int myPID = getpid();
		int shmem;
		/*****  Open File to hold Shared Memory ID  *****/

		if((fp = fopen("Balance","r")) == NULL)
    		{
    			printf("Balance:  could not open file.\n");
    			return(0);
    		}
		/*****  Get Shared Memory ID and close file  *****/

    		fscanf(fp,"%d",&Balance);
		fscanf(fp,"%d",&mutex);
    		fclose(fp);

		/****   Attach to the shared memory  ******/

		Bal = (int *) shmat(Balance, NULL, SHM_RND);
		
		for(i = 0; i<16; i++)
		{
			currValue = (int) pow(2,i);
			if(fork() == 0)
			{
				if(fork() == 0)
					role = 1;
				break;
			}
			myID++;
		}
		//Doesnt run the main ID
		if(getpid() != myPID)
		{
			//Loop to run N amount of times
			for(i = 0; i < N; i++)
			{
				//Checks to see if child
				if (role == 0)
   				{
    					for (i=0; i< N; i++)
       					{
         					p(0, mutex);
         					printf("\t\t%d - %d = %d\n",*Bal,currValue,(*Bal - currValue));
						*Bal -= currValue;
         					v(0, mutex);
       					}
   				}
				//Not child so Parent
				else
   				{
    					for (i=0; i< N; i++)
       					{
         					p(0, mutex);
         					printf("%d + %d = %d\n",*Bal,currValue,(*Bal + currValue));
						*Bal += currValue;
         					v(0, mutex);
       					}
				}
			}
		}
	}
	else if(strcmp(argv[1],"balance") == 0)			//Checks if balance is in the argv[1]
	{
		/*****  Open File to hold Shared Memory ID  *****/

                if((fp = fopen("Balance","r")) == NULL)
                {
                        printf("Could not open file.\n");
                        return(0);
                }


                /*****  Get Shared Memory ID and close file  *****/

                fscanf(fp,"%d",&Balance);
                fscanf(fp,"%d",&mutex);
                fclose(fp);

                /****   Attach to the shared memory  ******/

                Bal = (int*) shmat(Balance, NULL, SHM_RND);

		printf("Current Balance: %d\n", *Bal);
		return 0;
	}

	else if(strcmp(argv[1],"die") == 0)			//Checks if die is in argv[1]
	{
		/*****  Open File to hold Shared Memory ID  *****/

		if((fp = fopen("Balance","r")) == NULL)
    		{
    			printf("Could not open file.\n");
    			return(0);
    		}


		/*****  Get Shared Memory ID and close file  *****/

    		fscanf(fp,"%d",&Balance);
		fscanf(fp,"%d",&mutex);
    		fclose(fp);
		
		/****   Attach to the shared memory  ******/

		Bal = (int*) shmat(Balance, NULL, SHM_RND);
		
		printf("Balance: %d\n",*Bal);
		/****   Clean-up the shared memory  ******/

		if ((shmctl(Balance, IPC_RMID, NULL)) == -1)
    			printf("Error in removing shmem.\n");
		//Clean up sems
		if ((semctl(mutex, 0, IPC_RMID, 0)) == -1)
       			printf("%s", "Parent: ERROR in removing sem\n");

		/****   Cleanup Everything and go home...  ****/

		system("rm Balance");
	}
	else
		printf("Not valid, try again\n");		//Checks if any arg is not equal to the other conditions
		
	return 0;
}
/******* Code for p() and v() *********/
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
