#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *fileName = (char *)malloc(sizeof(char*)*20);
    printf("Specify file name you would like to print to: \n");
    scanf("%s",fileName);
	
    FILE* file1 = fopen(fileName, "a+");
 
    char c;
    c = getchar();
    c = getchar();
    while (c != '\n')
    {
        fprintf(file1,"%c",c);
	c = getchar();
    }
 
    fclose(file1);
 
    printf("CTRL+d is a correct ending");
 
    return 0;
}
