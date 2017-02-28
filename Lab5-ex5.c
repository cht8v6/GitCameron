#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    char *a = malloc(sizeof(char*)*10);
    a = "hey";
    a = "hello";   
    printf("%s\n",a);
return 0;
}
