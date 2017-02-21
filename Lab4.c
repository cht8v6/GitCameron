/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* fileNumber(char argv[],int*,int*, int*);
void offsetValue(char argv[], int*, int,int);
void scaleFactor(char argv[], int*, int, int);
void renameFile(char argv[], int*, int,int);
void help();
void getStatistics(int*,int,int,int);
void centerSignal(int*, int, int);
void normalizeSignal(int*, int, int, int);


    
int main(int argc, char *argv[]){
    int i;
    int* data = (int*)malloc(sizeof(int*)*1000);
    int count = argc;
    int fileNum;
    int maxNum;
    int size;
    
//    if(argc < 1 || argv[1][0] != '-'){
        for(i = 1; i < argc; i++){
            if(argv[i][0] == '-'){ //for loop to find file number before other commands
                if(argv[i][1] == 'n'){
                    if(argv[i+1] == NULL){
                        printf("Invalid input!\n\n");
                        help();
                    }
                    else{
                    data = fileNumber(argv[i+1], &fileNum, &maxNum, &size);
                    }
                }
            }
        }
        for(i = 1; i < count; i++){
            if(argv[i][0] == '-'){
                if(argv[i][1] == 'o'){
                    if(argv[i+1] == NULL){
                        printf("Invalid input!\n\n");
                        help();
                    }
                    else{
                    offsetValue(argv[i+1], data, fileNum, size);
                    }
                }
                if(argv[i][1] == 's'){
                    if(argv[i+1] == NULL){
                        printf("Invalid input!\n\n");
                        help();
                    }
                    else{
                    scaleFactor(argv[i+1], data, fileNum,size);
                    }
                }
            }
        }
        for(i = 1; i < argc; i++){
            if(argv[i][0] == '-'){
                if(argv[i][1] == 'r'){
                    if(argv[i+1] == NULL){
                        printf("Invalid input!\n\n");
                        help();
                    }
                    else{
                    renameFile(argv[i+1], data, maxNum,size);
                    }
                }
                if(argv[i][1] == 'h'){
                    help();
                }
                if(argv[i][1] == 'S'){
                    getStatistics(data,fileNum,size, maxNum);
                }
                if(argv[i][1] == 'C'){
                    centerSignal(data, fileNum, size);
                }
                if(argv[i][1] == 'N'){
                    normalizeSignal(data, maxNum, fileNum,size);
                }
            }
        }
    //}
//    else{     
//        printf("\n\nIncorrect Input, Options:\n\n-n\tFile number (value needed)\n-o\tOffset value (value needed)\n-s\tscale factor (value needed)\n-r\tRename files (name needed)\n-h\tHelp (examples)\n-S\tGet Statistics\n-C\tCenter the Signal\n-N\tNormalize signal\n\n");
//    }
	return 0;
}

int* fileNumber(char *argv,int* fileNum,int* maxNum, int* size){
    char str[16];
    FILE *fp;
    int num[2];
    int x;
    *fileNum = atoi(argv);
    //printf("fileNum = %d\n\n",*fileNum);
    int i;
    printf("New Files Created:\n");
    
    if(*fileNum < 10){
        sprintf(str,"Raw_data_0%d.txt",*fileNum);
        puts(str);
    }
    else{
        sprintf(str,"Raw_data_%d.txt",*fileNum);
        puts(str);
    }

    if((fp = fopen(str,"r")) == NULL){
        printf("Unable");
    }

    
    for(i = 0; i < 2; i++){
        fscanf(fp, "%d", &num[i]);
    }
    
    *size = num[0]; //calling by reference to use in other functions
    *maxNum = num[1];
    int *data = malloc(sizeof(int)* (*size));
    for(i = 0; i < *size; i++){
        fscanf(fp,"%d", &data[i]); //scanning data from selected file into pointer.
    }
    
//    offsetValue("2.5",data,fileNum,size);
//    scaleFactor(".5",data,fileNum);
//    renameFile("Cameron.txt",data,maxNum);
//        getStatistics(data,size);
//    help();
//    centerSignal(data,fileNum, size);
//    normalizeSignal(data,maxNum,fileNum);
    fclose(fp);
    return data;
}

void offsetValue(char argv[], int *data, int fileNum,int size){
    char *ptr;
    double offset = strtod(argv, &ptr);
    int i;
    char *off[18];
    double *data2 = (double*)malloc(sizeof(double*)*(size));
    for(i = 0; i < size; i++){
        data2[i] = (double)data[i]; //setting new pointer to values so i can use same values later in my code
        
    }
    for(i = 0; i < size; i++){
        data2[i] += offset;
    }
    FILE *fp;
    if(fileNum < 10){
        sprintf(off,"Offset_data_0%d.txt",fileNum);
        puts(off);
    }
    else{
        sprintf(off,"Offset_data_%d.txt",fileNum);
        puts(off);
    }
    if((fp = fopen(off,"w")) == NULL)
        printf("Unable");
    

    fprintf(fp, "%d %.4f\n", size, offset);
    for(i = 0; i < size; i++){
        fprintf(fp,"%.4f\n",data2[i]);
    }
    fclose(fp);
}

void scaleFactor(char argv[], int *data, int fileNum,int size){
    char *ptr;
    double scale = strtod(argv, &ptr);
    int i;
    char *sc[18];
    double *data2 = malloc(sizeof(double)*(size));
    for(i = 0; i < size; i++){
        data2[i] = (double)data[i];
    }
    for(i = 0; i < size; i++){
        data2[i] *= scale;  //multiplying each element by scale
    }
    FILE *fp;
    if(fileNum < 10){
        sprintf(sc,"Scaled_data_0%d.txt",fileNum);
        puts(sc);
    }
    else{
        sprintf(sc,"Scaled_data_%d.txt",fileNum);
        puts(sc);
    }
    if((fp = fopen(sc,"w")) == NULL) 
        printf("Unable to Open");
    
    fprintf(fp, "%d %.4f\n", size, scale);
    for(i = 0; i < size; i++){
        fprintf(fp,"%.4f\n",data2[i]);
    }
    fclose(fp);
    
}

void renameFile(char argv[], int *data, int maxNum,int size){
    FILE *fp;
    if((fp = fopen(argv,"w")) == NULL) //string name was argument
    {
        printf("Unable to Open");
    }
    puts(argv);
    fprintf(fp, "%d %d\n",size, maxNum);
    
    int i;
    for(i = 0; i < size; i++){
        fprintf(fp,"%d\n",data[i]);
    }
    fclose(fp);
}

void help(){
    printf("\n\nOptions:\n\n-n\tFile number (value needed)\n-o\tOffset value (value needed)\n-s\tscale factor (value needed)\n-r\tRename files (name needed)\n-h\tHelp (examples)\n-S\tGet Statistics\n-C\tCenter the Signal\n-N\tNormalize signal\n\n");
    printf("\nExamples:\n./Lab4.c -n 3 -o 2.5\n./Lab4.c -s 1.7 -n 10\n./Lab4.c -n 2 -r NewName.txt\n./Lab4.c -n 2 -r NewName.txt -s 3\n");
    
}

void getStatistics(int *data,int fileNum,int size,int maxNum){
    double average = 0;
    double total = 0;
    int i;
    char *stat[22];
    int amount = size;
    for(i = 0; i < size; i++){
        total += (double)data[i]; //added all the data together and divided by size to get average.
    }
    average = total/amount;
    FILE *fp;
    if(fileNum < 10){
        sprintf(stat,"Statistics_data_0%d.txt",fileNum);
        puts(stat);
    }
    else{
        sprintf(stat,"Statistics_data_%d.txt",fileNum);
        puts(stat);
    }
    if((fp = fopen(stat,"w")) == NULL)
        printf("Unable");
    fprintf(fp,"%f %d",average,maxNum);
}

void centerSignal(int *data, int fileNum, int size){
    double average = 0;
    double total = 0;
    int i;
    for(i = 0; i < size; i++)
    {
        total += (double)data[i];
    }
    average = total/size; //found average and subtracted every value by the average.
    char *ptr;
    double offset = average;
    char *off[18];
    double *data2 = malloc(sizeof(double)*(size));
    
    for(i = 0; i < size; i++){
        data2[i] = (double)data[i];
//        printf("%f\n",data2[i]);
    }
    for(i = 0; i < size; i++){
        data2[i] -= offset;
    }
    
    FILE *fp;
    if(fileNum < 10){
        sprintf(off,"Centered_data_0%d.txt",fileNum);
        puts(off);
    }
    else{
        sprintf(off,"Centered_data_%d.txt",fileNum);
        puts(off);
    }
    if((fp = fopen(off,"w")) == NULL)
        printf("Unable");
    
    fprintf(fp, "%d %.4f\n", size, -offset);
    for(i = 0; i < size; i++){
        fprintf(fp,"%.4f\n",data2[i]);
    }
    
}

void normalizeSignal(int *data, int maxNum, int fileNum, int size){
    char *ptr;
    double scale = (double)maxNum;
    int i;
    char *sc[18];
    double *data2 = malloc(sizeof(double)*(size));
    for(i = 0; i < size; i++){
        data2[i] = (double)data[i];
    }
    for(i = 0; i < size; i++){
        data2[i] /= scale;// used the maxNum and divided every value by it to make the results between 0 and 1
    }
    FILE *fp;
    if(fileNum < 10){
        sprintf(sc,"Normalized_data_0%d.txt",fileNum);
        puts(sc);
    }
    else{
        sprintf(sc,"Normalized_data_%d.txt",fileNum);
        puts(sc);
    }
    if((fp = fopen(sc,"w")) == NULL)
        printf("Unable to Open");
    double num = 1/(double)scale;
    
    fprintf(fp, "%d %.4f\n", size, num);
    for(i = 0; i < size; i++){
        fprintf(fp,"%.4f\n",data2[i]);
    }
    
}
