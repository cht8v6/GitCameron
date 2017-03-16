/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class Signal{
		
    private:
        int i;
        double *data;
        int size;
	double average;
	int maxNum;
	int fileNumber;
	double *data2; 
        int err;
			
    public:
	
	Signal();
        Signal(int fileNumber); //input is filenumber
	Signal(const char *name);
        ~Signal();
        //int* fileNumber();
	void offsetValue(double); //option number 1
	void scaleFactor(double); //option number 2
	void getStatistics(); 
	void centerSignal(); //option number 3
	void normalizeSignal(); // option number 4
	void Sig_info();
	void Save_file(int, int);
        int geterr(); //needed to access err variable in main
};


Signal::Signal(const char *name){
    data = new double [size];
    FILE *fp = fopen(name,"r");
    if(fp == NULL){
	cout << "invalid name of file";
	err = -1; //flag to end program
        return;
    }
    fscanf(fp,"%d %d",&size,&maxNum);
    cout << "MaxNum is :" << maxNum << endl;
    for(i = 0; i < size; i++){
	fscanf(fp,"%2lf",&data[i]);
    }
    cout << "Signal\n" <<endl;
    for(i = 0; i < size; i++){
	cout << data[i] << endl;
    }
    fclose(fp);
}
//Signal::

Signal::Signal(){
    i= 0;
    data = NULL;
    size = 0;
    average = 0.0;
    maxNum = 0;
    fileNumber = 0;
    data2 = NULL;
    err = 0;
}

Signal::Signal(int fileNum){
    fileNumber = fileNum;
    char str[20];
    FILE *fp;
        
    if(fileNumber < 10){
    sprintf(str,"Raw_data_0%d.txt",fileNumber);
    puts(str);
    }
    else{
    sprintf(str,"Raw_data_%d.txt",fileNumber);
    puts(str);
    }
        
    if((fp = fopen(str,"r")) == NULL){
        cout << "Unable to open file" << endl;
        return;
    }
        
    fscanf(fp,"%d %d",&size,&maxNum);
    data = new double [size];
    for(i = 0; i < size; i++){
	fscanf(fp,"%2lf",&data[i]);
    }
    cout << "Signal\n" <<endl;
    for(i = 0; i < size; i++){
    	cout << data[i] << endl;
    }
    fclose(fp);        
}

//option passes which procedure was done

void Signal::Save_file(int fileNum, int option){
    fileNumber = fileNum;
    char name[20];
    FILE *fp;
    
    switch(option){
        case 0: {
            cout << "Please select procedure before save" <<endl;
            break;
        }
        case 1: {
             if(fileNumber < 10){
                sprintf(name,"Offset_data_0%d.txt",fileNumber);
                puts(name);
            }
            else{
                sprintf(name,"Offset_data_%d.txt",fileNumber);
                puts(name);
            }
            break;
        }
        case 2: {
            if(fileNumber < 10){
                sprintf(name,"Scale_data_0%d.txt",fileNumber);
                puts(name);
            }
            else{
                sprintf(name,"Scale_data_%d.txt",fileNumber);
                puts(name);
            }
            break;
        }
        case 3: {
            if(fileNumber < 10){
                sprintf(name,"Centered_data_0%d.txt",fileNumber);
                puts(name);
            }
            else{
                sprintf(name,"Centered_data_%d.txt",fileNumber);
                puts(name);
            }
            break;
        }
        case 4: {
            if(fileNumber < 10){
                sprintf(name,"Normalized_data_0%d.txt",fileNumber);
                puts(name);
            }
            else{
                sprintf(name,"Normalized_data_%d.txt",fileNumber);
                puts(name);
            }
            break;
        }
    }
    
    if((fp = fopen(name,"w")) == NULL){
        cout << "Unable to open file" << endl;
        return;
    }
    else{
    fprintf(fp,"%d %d",size,maxNum);
    for(i = 0; i < size; i++){
        fprintf(fp,"%.4f\n",data2[i]);
    }
    }
    fclose(fp);
}

int Signal::geterr(){
    return err;
}

void Signal::Sig_info(){
    cout<< "Info\nMax Number: " << maxNum << "\nSize: " << size << "\nAverage: " << average <<endl;        
}

void Signal::getStatistics(){
    double total = 0;
    
    for(i = 0; i < size; i++){ //finding average
        total += data[i];
    }
    average = total/size;
    //printing statistics
    cout<< average<< endl
            << maxNum << endl;
}

void Signal::scaleFactor(double scale){
    data2 = new double [size];
    for(i = 0; i < size; i++){
        data2[i] = data[i];
    } //assigning original values to new array
    for(i = 0; i < size; i++){
        data2[i] *= scale;
    } //scaling those values
    cout << "the signal after scaled is:\n";
    for(i = 0; i < size; i++){
    	cout << data2[i] << endl;
    }
}

void Signal::offsetValue(double offset){
    data2 = new double[size];
    for(i = 0; i < size; i++){
        data2[i] = data[i];
    } //assigning original values to new array
    for(i = 0; i < size; i++){
        data2[i] += offset;
    } //offsetting values
    cout << "the signal after offset is:\n";
    for(i = 0; i < size; i++){
    	cout << data2[i] << endl;
    }
}

void Signal::centerSignal(){
    data2 = new double [size];
    double total = 0;
    
    for(i = 0; i < size; i++){
        total += data[i];
    }
    average = total/size; //finding average
    double offset = (double)average;
    cout << "Average" << average << endl;
    for(i = 0; i < size; i++){
        data2[i] = data[i];
    } //assigning original values to new array
    for(i = 0; i < size; i++){
        data2[i] *= offset;
    } //centering data
    cout << "the signal centered is:\n";
    for(i = 0; i < size; i++){
    	cout << data2[i] << endl;
    }
}

void Signal::normalizeSignal(){
    data2 = new double [size];
    double scale = 1 / (double)maxNum; // normalizing the data
    for(i = 0; i < size; i++){
        data2[i] = data[i];
    } //assigning original values to new array
    cout << "Scale" << scale << endl;
    for(i = 0; i < size; i++){
        data2[i] *= scale;
    } //normalizing data
    cout << "the signal after Normalized is:\n";
    for(i = 0; i < size; i++){
    	cout << data2[i] << endl;
    }
}

int main(int argc, char* argv[]){
    int i;
    char name[25];
    int fileNum;
    int select;
    int offset;
    int scale;
    int option = 0;
	
	
    Signal *signal;
	//determining input and error checking
    if(argc == 3){
	if(argv[1][0] == '-'){
            if(argv[1][1] == 'n'){
		if(isdigit(*argv[2])){
                    fileNum = atoi (*(argv+2));
			signal = new Signal(fileNum);
		}else{
                    cout << "Error: invalid input\n valid input: \n\t ./a.out -n fileNumber \n\t ./a.out -n FileName" << endl;
			return 0;
                }
            }
            else 
            if(argv[1][1] == 'f'){
                if(isdigit(*argv[2])){
                    cout << "Error: invalid input\n valid input: \n\t ./a.out -n fileNumber \n\t ./a.out -n FileName" << endl;
			return 0;
		}
                else{
                   // std::string name = argv[2];
                    strcpy(name, argv[2]);
                    signal = new Signal(name);
                }
            }
            else{
		cout << "Error: invalid input\n valid input: \n\t ./a.out -n fileNumber \n\t ./a.out -n FileName" << endl;
                    return 0;
            }
	}
	else{
		cout << "Error: invalid input\n valid input: \n\t ./a.out -n fileNumber \n\t ./a.out -n FileName" << endl;
		return 0;
	}
    }
    else if(argc == 1){
            cout << "No command \n\n Please Enter FileName: ";
            cin >> name;
            signal = new Signal(name);
	}
    else{
    	cout << "Error: invalid input\n valid input: \n\t ./a.out -n fileNumber \n\t ./a.out -n FileName" << endl;
	return 0;
    }
    
    if(signal->geterr() == -1){ //if file entered was not valid
        return 0;
    }
	//options for user
    int x;
    while(x == 0){
        cout << "What would you like to do?\n\t 1:Offset\n\t 2:Scale\n\t 3:Center \n\t 4:Normalize \n\t 5:Statistics \n\t 6:Get Signal Info \n\t 7:Save File \n\t 8:Exit"<<endl;
	cin >> select;
        while(select > 9 || select < 1){
            cout << "Please enter valid choice" << endl;
            cin >> select;
	}
		
	if(select == 1){ //offset
            option = 1;
            cout << "Enter offset value" << endl;
            cin >> offset;
            signal->offsetValue(offset);
	}
	else if(select == 2){ //scale
            option = 2;
            cout << "Enter vale to scale" << endl;
            cin >> scale;
            signal->scaleFactor(scale);
	}
	else if(select == 3){ //center
                option = 3;
                signal->centerSignal();
	}
	else if(select == 4){ //normalize 
                option = 4;
                signal->normalizeSignal();
	}
	else if(select == 5){ //statistics
		signal->getStatistics();
	}
	else if(select == 6){ //info
		signal->Sig_info();
	}
	else if(select == 7){  //save
		signal->Save_file(fileNum, option);
        }
	else if(select == 8){ //exit
		x = 1;
		return 0;
	}
    }
}