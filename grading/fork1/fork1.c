//Colin O'Neal
//CSC 460
//2-1-17
//Fork1-C Program
//Found in: Home/oneal_wc/csc460/grading/fork1/fork1.c

#include<stdio.h>
int main(int args, char ** argv)
{
int x, i, j;
int Gen = 0;
int N = atoi(argv[1]);						//Sets a variable N equal to user input after a.out

printf("Gen\tPID\tPPID\n\n");					//Prints the column headers

for(i=1; i<=N; i++)						//loop that will fork the child processes n amount of times
{
	x = fork();
	if(x==0)						//When the child process ID is 0 it will increment genration
	{
		Gen++;
		i = 0;
		N--;
	}
}
printf("%d\t%d\t%d\n",Gen,getpid(),getppid());

sleep(1);

return 0;							//End of program
}
