#include<stdio.h>
#include<stdlib.h>

int main()
{
	int x=1309;
	int *p = malloc(sizeof(int*)*10);
	p = NULL;
	printf("\n The value of x is = %d",x);
if(p)	
	printf("\n The pointer points to the value = %d",*p);
else
	printf("\nThe pointer points to NULL"); 	
return 1;
}
