//Colin O'Neal
//Lucy's List
//2-20-17
//$HOME/csc460/grading/bb

#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

struct bbStruct
{
        int id;
        char name[20];
        int favNum;
        char favFood[30];
};

main(int argc, char *argv[])
{
int shmid,i;
struct bbStruct *shmem;
FILE *fopen(), *fp;
char food[30];
strcpy(food, argv[1]);

/*****  Open File to hold Shared Memory ID  *****/

if((fp = fopen("/pub/csc460/bb/BBID.txt","r")) == NULL)
    {
    printf("watch:  could not open file.\n");
    return(0);
    }

/*****  Get Shared Memory ID and close file  *****/

    fscanf(fp,"%d",&shmid);
    fclose(fp);

shmem = (struct bbStruct *) shmat(shmid, NULL, SHM_RND);

printf("\n\nHERE IS OUR SHARED MEMORY:\n\n");				//Changes the variable by going through entire shmem to check for my name then prints
for (i=0;i<21;i++)
    {
	if(strcmp(shmem->name, "O'Neal, Colin") == 0)			//Checks for my name then if it finds it goes to the favFood
		strncpy(shmem->favFood, food, 30);
       printf("%2d: %20s| %8d| %30s|\n",shmem->id,shmem->name,shmem->favNum,shmem->favFood);
       shmem++;
    }
printf("\n\n");
}
