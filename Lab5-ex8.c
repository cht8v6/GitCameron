#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
	char *s, *dyn_s;
	s = malloc(sizeof(char*)*20);
	int ln;
	printf("Enter the input string\n");
	scanf("%s",s);
	ln = strlen(s);
	dyn_s = (char*)malloc(ln+1);
	dyn_s = s;
	dyn_s[ln]='\0';
	printf("%s \n",dyn_s);
	return 0;
}

