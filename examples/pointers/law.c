#include<stdio.h>

int main()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int *d;
	d = &a;
	*d = 460;
	int **e = &d;
	**e = 100;
	int x[5];
	x[0] = 500;
	x[1] = 250;
	a = x[1];
	
	d = x;
	d[2] = -123;
	a = x[2];

	d++;
	a = *d;

	*(d - 1) = 999;
	a = x[0];

	printf("a is %d\n",a);

	return 0;
}
