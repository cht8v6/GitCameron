#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char *p = (char*)malloc(sizeof(char*)*10);
    strcpy(p,"Mizzou");
    p[ 3 ] = 'P';
    printf("%s\n",p);
return 0;
}
