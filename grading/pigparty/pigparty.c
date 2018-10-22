//Colin O'Neal
//Pig-Pen Party
//3-27-17
//$HOME/csc460/grading/pigparty

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int chopsticks;
	int phnum = 0, x = 0, i;
	int N = 5;
	//Asks for semaphores 
	chopsticks = semget(IPC_PRIVATE, 5, 0777);
	//  See if you got the request.
	if (chopsticks == -1)
   	{
    		printf("%s","Chopsticks Failed.\n");
    		return (-1);
   	}
	//  Initialize your sems.
	semctl(chopsticks, 0, SETVAL, 1);
	semctl(chopsticks, 1, SETVAL, 1);
	semctl(chopsticks, 2, SETVAL, 1);
	semctl(chopsticks, 3, SETVAL, 1);
	semctl(chopsticks, 4, SETVAL, 1);
	//Forks to make 5 philosophers
	for(i = 1; i<N; i++)
	{
		if(fork() == 0)
			break;
		phnum++;
		if(phnum > 4)
			phnum = 0; 
	}
	
	//Infinite loop
	while(x == 0)
	{
		think(phnum);
		for(i = 0; i<=999999; i++) {}		//Loop to waste time
		hungry(phnum);
		p(phnum, chopsticks);				//Picks up left chopstick
		p((phnum+1)%5, chopsticks);				//Picks up right chopstick
		eat(phnum);
		for(i = 0; i<=999999; i++) {}		//Loop to waste time
		v((phnum+1)%5, chopsticks);			//Puts down right chopstick
		v(phnum, chopsticks);				//Puts down left chopstick
	}

	return 0;
}
//Method used to print Thinking with phnum # of tabs
think(int phnum)
{
	if(phnum == 0)
		printf("%d Thinking\n",phnum);
	else if(phnum == 1)
		printf("\t%d Thinking\n",phnum);
	else if(phnum == 2)
		printf("\t\t%d Thinking\n",phnum);
	else if(phnum == 3)
		printf("\t\t\t%d Thinking\n",phnum);
	else
		printf("\t\t\t\t%d Thinking\n",phnum);
}
//Method to print Hungry phnum # of tabs
hungry(int phnum)
{
        if(phnum == 0)
                printf("%d Hungry\n",phnum);
        else if(phnum == 1)
                printf("\t%d Hungry\n",phnum);
        else if(phnum == 2)
                printf("\t\t%d Hungry\n",phnum);
        else if(phnum == 3)
                printf("\t\t\t%d Hungry\n",phnum);
        else
                printf("\t\t\t\t%d Hungry\n",phnum);
}
//Method to print Eat phnum # of tabs
eat(int phnum)
{
        if(phnum == 0)
                printf("%d Eating\n",phnum);
        else if(phnum == 1)
                printf("\t%d Eating\n",phnum);
        else if(phnum == 2)
                printf("\t\t%d Eating\n",phnum);
        else if(phnum == 3)
                printf("\t\t\t%d Eating\n",phnum);
        else
                printf("\t\t\t\t%d Eating\n",phnum);
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
