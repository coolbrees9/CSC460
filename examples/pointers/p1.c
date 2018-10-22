#include <stdio.h>

main()
{
int x = 3;
char c = 'A';
int num[10];
int *vals;

int i;
for (i=0;i<10;i++)
   num[i] = i*10;

vals = num;

printf("%d\t%c\t%d\t%d\n",x,c,num[0],*vals);
vals++;
printf("%d\t%c\t%d\t%d\n",x,c,num[0],*vals);
c++;
vals++;
printf("%d\t%c\t%d\t%d\n",x,c,num[0],*vals);

for (vals = num; vals < &(num[10]) ; vals++)
    printf("%d\n",*vals);

}








