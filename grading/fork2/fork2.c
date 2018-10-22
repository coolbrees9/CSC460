//Colin O'Neal
//CSC460
//2-8-17
//Fork 2- Bad Sync Program
//Can be found on intruder in: $HOME/csc460/grading/fork2/fork2.c
#include<stdio.h>

int main(int argc, char *argv[])
{
	FILE *fopen(), *fp;

	if((fp = fopen("syncfile","w")) == NULL)
    	{
    		printf(":( could not open myLittleFile to write.\n");
    		return(0);
    	}
	fprintf(fp,"%c",'A');
	fclose(fp);
	int N;
	if(argc > 1)
		N = atoi(argv[1]);
	else
		printf("Wrong ");
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
		for( i = 0; i < N-1; i++)							//Runs while i is less than the number entered after a.out
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
         			if((fp = fopen("syncfile","r")) == NULL)
             			{
             				printf(":( could not open syncfile to read.\n");
             				return(0);
             			}

             			fscanf(fp,"%c",&found);
             			fclose(fp);
     			}

     			printf("%c: %d\n",id,getpid());					//Print statement that prints it out in order

     			if((fp = fopen("syncfile","w")) == NULL)
         		{
         			printf(":( could not open myLittleFile to write.\n");
         			return(0);
         		}
     			fprintf(fp,"%c",otherId);
     			fclose(fp);							//Closes the file and ends
			
		}
	sleep(1);
	return 0;
	}
}
