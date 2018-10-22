#include<stdio.h>
//19
struct T1struct ()
{
	int value;
	struct T1struct *ptr;
};
int main()
{
//20
struct T1struct *T1ptr;
T1ptr = (struct T1struct *) malloc(3*sizeof(struct T1struct));

//21
struct T1struct **T1ptr2 = &T1ptr;

//22
(*T1ptr2) -> value = 460;
(*(*T1ptr2)).value = 460;

//23
T1ptr[0].value = 1;
T1ptr[1].value = 2;
T1ptr[2].value = 3;

//24
struct T1struct *tmp;
tmp = T1ptr;
tmp++;
T1ptr -> ptr = tmp;
tmp++;
T1ptr -> ptr -> ptr = tmp;
tmp -> ptr = T1ptr;
	
return 0;
}
