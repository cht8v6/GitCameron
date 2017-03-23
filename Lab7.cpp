/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Signal{
    private:
        int err;
			
    public:
	
        int i;
        int size;
	double average;
        double maxNum;
	int fileNumber;
        string name;
        vector<double> data;
        void Average();
        
	Signal();
        Signal(int fileNumber); //input is filenumber
	Signal(string name);
        ~Signal();
        //int* fileNumber();
	void offsetValue(double offset, Signal &sig); //option number 1
	void scaleFactor(double scale, Signal &sig ); //option number 2
	void getStatistics(); 
	void centerSignal(Signal &sig); //option number 3
	void normalizeSignal(Signal &sig); // option number 4
	void Sig_info();
        void operator+(double offset);
        void operator*(double scale);
	void Save_file(int);
        int geterr();//needed to access err variable in main
//        int getSize();
//        double getMaxNum();
//        vector<double> getData();
};

//int Signal::getSize(){
//    return size;
//}
//double Signal::getMaxNum(){
//    return maxNum;
//}
//
//vector<double> Signal::getData(){
//    return data;
//}

Signal::Signal(){
    i= 0;
    size = 0;
    average = 0.0;
    maxNum = 0;
    fileNumber = 0;
    err = 0;

}

Signal::Signal(string name){
    i= 0;
    size = 0;
    average = 0.0;
    maxNum = 0;
    fileNumber = 0;
    err = 0;
//    cout << "Worked" << endl;
    std::fstream infile;
    infile.open(name.c_str(),ios::in); //open file
    
    if(!infile){ //check if file wasn't opened
	cout << "invalid name of file";
	err = -1; //flag to end program
        return;
    }
    infile >> size; //reading in size
    vector<double> data3 (size, 0); //creating a vector
    data = data3;
    
    infile >> maxNum; //reading in maxNum
//    fscanf(fp,"%d %d",&size,&maxNum);
//    cout << "MaxNum is :" << maxNum << endl;
    for(i = 0; i < size; i++){
        infile >> data[i]; //reading in signal from file
//	fscanf(fp,"%2lf",&data[i]);
    }
    Average();
    cout << "Signal" << endl ;
    cout << size << " " << maxNum << endl; //next lines printing out Signal
    for(i = 0; i < size; i++){
	cout << data[i] << endl; 
    }
    infile.close();
    return;
}




Signal::Signal(int fileNum){
    i= 0;
    size = 0;
    average = 0.0;
    maxNum = 0;
    fileNumber = 0;
    err = 0;
    fileNumber = fileNum;
    string name;
    ostringstream conv; //using conversion to make fileNum strings
    ostringstream vert; //using to put 0 in front of fileNum if less than 10
    if(fileNumber < 10){
        int zero = 0;
        vert << zero;
    }
    conv << fileNumber;
    string zer = vert.str();
    name = conv.str();
    string beg = "Raw_data_";
    string ending = ".txt";
    if(fileNumber < 10){
        name = beg + zer + name + ending;
    }
    else{
        name = beg + name + ending;
    }
    cout << name << endl;
    
    ifstream infile;
    infile.open(name.c_str(),ios::in);    
//    if(fileNumber < 10){ 
//    sprintf(str,"Raw_data_0%d.txt",fileNumber);
//    puts(str);
//    }
//    else{
//    sprintf(str,"Raw_data_%d.txt",fileNumber);
//    puts(str);
//    }
//    if((fp = fopen(str,"r")) == NULL){
//        cout << "Unable to open file" << endl;
//        return;
//    }
    if(!infile){ //check if file wasn't opened
	cout << "invalid name of file";
	err = -1; //flag to end program
        return;
    }
    infile >> size;
    infile >> maxNum;
    vector<double> data3(size, 0);
    data = data3;
//    fscanf(fp,"%d %d",&size,&maxNum);
    for(i = 0; i < size; i++){
        infile >> data[i];
    }
    Average();
    cout << size << " " << maxNum << endl;
    for(i = 0; i < size; i++){
    	cout << data[i] << endl;
    }
    infile.close();       
    return;
}

Signal::~Signal(){
} //function not needed because using vectors instead of arrays
//nothing to free


void Signal::operator+(double offset){
 //   vector<double> data(size);
//    for(i = 0; i < size; i++){
//        cout<< "i = " << i << endl;
//        data[i] = offset + data[i];
//        cout<<data[i]<< endl;
//    }
    maxNum = 0;
    for(i =0; i < size; i++){
//        data2[i] = data[i] + offset;
        data[i] = data[i] + offset;
        if(data[i] > maxNum){
            maxNum = data[i];
        }
    }
    cout << "new Signal:" << endl;
    cout << size << " " << maxNum  << endl;
    for(i = 0 ; i < size; i++){
        cout << data[i] << endl;
    }
    Average();
}

void Signal::operator *(double scale){
    maxNum = 0;
    for(i = 0; i < size; i++){
        data[i] = scale * data[i];
        if(data[i] > maxNum){
            maxNum = data[i];
        }
    }
    
    cout << "new Signal:" << endl;
    cout << size << " " << maxNum << endl;
    for(i = 0 ; i < size; i++){
        cout << data[i] << endl;
    }
    
}
//option passes which procedure was done

void Signal::Save_file(int option){
    string name;

    string ending = ".txt";
//    ofstream out;
    
    switch(option){
        case 0: {
            cout << "Please select procedure before save" <<endl;
            break;
        }
        case 1: {

                string beg = "Offset_data";
                string ending = ".txt";
                name = beg + ending;
                cout << name << endl;
            break;
        }
        case 2: {

                string beg = "Scaled_data";
                name = beg + ending;
                cout << name << endl;
            break;
        }
        case 3: {

                string beg = "Centered_data";
                name = beg + ending;
                cout << name << endl;
            break;
        }
        case 4: {
                string beg = "Normalized_data";
                name = beg + name + ending;
                cout << name << endl;
            break;
        }
    }
    std::ofstream save;
    save.open(name.c_str(),ios::out);
    save << size << " " << maxNum << endl;
    for(i = 0; i < size; i++){
        save << data[i] << endl;
    }
    save.close();
//    if(!out){
//        cout << "Unable to open file" << endl;
//        return;
//    }
//    else{
//        out << size << " " << maxNum << endl;
//        for(i = 0; i < size; i++){
//            out << data[i] << endl;;
//        }   
//    }
//    out.close();
}

int Signal::geterr(){
    return err;
}

void Signal::Sig_info(){
    cout<< "Info\nMax Number: " << maxNum << "\nSize: " << size << "\nAverage: " << average <<endl;        
}

void Signal::getStatistics(){
    cout << "Average: " << average<< endl;
    cout << "Max Number: "<< maxNum << endl;
}

void Signal::Average(){
    double total = 0;
    
    for(i = 0; i < size; i++){ //finding average
        total = data[i] + total;
    }
    average = total/(double)size;
    
}

void Signal::scaleFactor(double scale, Signal &sig){
    sig * scale;
    Average();
//    for(i = 0; i < size; i++){
//        data[i] *= scale;
//    } //scaling those values
//    cout << "the signal after scaled is:\n";
//    for(i = 0; i < size; i++){
//    	cout << data[i] << endl;
//    }
}

void Signal::offsetValue(double offset, Signal &sig){ //assigning original values to new array
    sig + offset;
    Average();
//    for(i = 0; i < size; i++){
//        data[i] += offset;
//    } //offsetting values
//    cout << "the signal after offset is:\n";
//    for(i = 0; i < size; i++){
//    	cout << data[i] << endl;
//    }
}

void Signal::centerSignal(Signal &sig){
    Average();
    double offset = -(double)average;
    sig + offset;
//    double total = 0;
//    
//    for(i = 0; i < size; i++){
//        total += data[i];
//    }
//    average = total/size; //finding average
//    double offset = (double)average;
//    cout << "Average" << average << endl;
//    for(i = 0; i < size; i++){
//        data[i] *= offset;
//    } //centering data
//    cout << "the signal centered is:\n";
//    for(i = 0; i < size; i++){
//    	cout << data[i] << endl;
//    }
}

void Signal::normalizeSignal(Signal &sig){
    double scale = (1 / (double)maxNum); // normalizing the data
    sig * scale;
    Average();
//    cout << "Scale" << scale << endl;
//    for(i = 0; i < size; i++){
//        data[i] *= scale;
//    } //normalizing data
//    cout << "the signal after Normalized is:\n";
//    for(i = 0; i < size; i++){
//    	cout << data[i] << endl;
//    }
}

Signal operator+(Signal &signal1, Signal &signal2){
    Signal signal3;
    double total = 0;
    int i;
    int maxNumber = 0;
    
    vector<double> data3 (signal1.size, 0); //create vector size of signal
    signal3.data = data3;
    //below - i make sure they are the same size and then add them and put them into signal 3
    if(signal1.size == signal2.size){ 
        for(i = 0; i < signal1.size; i++){
            signal3.data[i] = signal1.data[i] + signal2.data[i];
//            cout << signal3.data[i] << endl;
        }
    }
    else{
        cout<< "Signals are different lengths" << endl;
        return 0;
    }
    
    cout<< "New signal data" <<endl;
    for(i = 0; i < signal1.size; i++){
        total = total + signal3.data[i];
        if(signal3.data[i] > maxNumber){
            maxNumber = signal3.data[i];
        }
    }
    signal3.size = signal1.size;
    signal3.maxNum = maxNumber;
    signal3.average = total/signal1.size;
    
    cout << signal3.size << " " << signal3.maxNum << endl;
    for(i = 0; i < signal3.size; i++){
        cout << signal3.data[i] << endl;
    }
    return signal3;
}

int main(int argc, char* argv[]){
    int i;
    string name;
    int fileNum;
    int select;
    int offset;
    int scale;
    int option = 0;
	
	
    Signal signal;
	//determining input and error checking
    if(argc == 3){
	if(argv[1][0] == '-'){
            if(argv[1][1] == 'n'){
		if(isdigit(*argv[2])){
                    fileNum = atoi (*(argv+2));
			signal = Signal(fileNum);
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
                   std::string name = argv[2];
//                    strcpy(name.c_str(), argv[2]);
                    signal = Signal(name);
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
            signal = Signal(name);
	}
    else{
    	cout << "Error: invalid input\n valid input: \n\t ./a.out -n fileNumber \n\t ./a.out -n FileName" << endl;
	return 0;
    }
    
    if(signal.geterr() == -1){ //if file entered was not valid
        return 0;
    }
    
	//options for user
    int x;
    while(x == 0){
        cout << "What would you like to do?\n\t 1:Offset\n\t 2:Scale\n\t 3:Center \n\t 4:Normalize \n\t 5:Statistics \n\t 6:Get Signal Info \n\t 7:Save File \n\t 8:Add vectors \n\t 9:Exit"<<endl;
	cin >> select;
        while(select > 9 || select < 1){
            cout << "Please enter valid choice" << endl;
            cin >> select;
	}
		
	if(select == 1){ //offset
            option = 1;
            cout << "Enter offset value" << endl;
            cin >> offset;
            signal.offsetValue(offset,signal);
	}
	else if(select == 2){ //scale
            option = 2;
            cout << "Enter vale to scale" << endl;
            cin >> scale;
            signal.scaleFactor(scale,signal);
	}
	else if(select == 3){ //center
                option = 3;
                signal.centerSignal(signal);
	}
	else if(select == 4){ //normalize 
                option = 4;
                signal.normalizeSignal(signal);
	}
	else if(select == 5){ //statistics
		signal.getStatistics();
	}
	else if(select == 6){ //info
		signal.Sig_info();
	}
	else if(select == 7){  //save
		signal.Save_file(option);
        }
        else if(select == 8){
            Signal signal1(1);
            Signal signal2(12);
            Signal signal3 = operator+(signal1,signal2);
        }
	else if(select == 9){ //exit
		x = 1;
		return 0;
	}
        
    }
}
