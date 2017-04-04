/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <cstring>

using namespace std;

class message {
    protected:
        string original;
        int size;
    
    public:
        message();
        message(string);
        ~message();
        virtual void printMessage();
};

class morseCodeMessage : public message{
    public:
        string *NewMessage;
        string morse;
        morseCodeMessage();
        ~morseCodeMessage();
        void Translate();
        void printMessage();
//        string getNewMessage();
};

class messageStack{
    public:
        message *stack[10];
        message *root;
        messageStack();
        ~messageStack();
        void push(message);
        void push(morseCodeMessage);
        void pop();
        void printStack();
        int num;
        int i;
};

message::message(){
    cout << "Enter a word: " << endl;
    cin >> original;
    size = original.length();
}

message::message(string original){
    this->original = original;
    size = original.length();
}

message::~message(){
    
}

void message::printMessage(){
    cout << "Original message: " << original << endl;
}

morseCodeMessage::morseCodeMessage() : message(){
    NewMessage = new string[size];
    Translate();
}

morseCodeMessage::~morseCodeMessage(){
//    delete[] NewMessage;
}

void morseCodeMessage::printMessage(){
    cout << "Morse Code: " << morse << endl;
    cout << "Original message: " << original << endl;
}

void morseCodeMessage::Translate(){
    int i;
    int place;
    string alphabet = "abcdefghijklmnopqrstuvwxyz123456789";
    string morsealphabet[36] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",    ".----","..---", "...--","....-",".....","-....","--...","---..","----.","-----" };
    
    for(i = 0; i < size; i++){
        if(isupper(original[i]) == 1){
            original[i] = (char)tolower(original[i]);
        }
    }
    
    for(i = 0; i < size; i++){
        place = alphabet.find(original[i]);
        NewMessage[i] = morsealphabet[place];
    }
    
    for(i = 0; i < size; i++){
        morse.append(NewMessage[i]);
        morse.append(" ");
    }
}
//string morseCodeMessage::getNewMessage(){
//    return morse;
//}

void messageStack::printStack(){
    int j;
    cout << "\n\nStack\n" << endl;
    for(j = 0; j < i; j++){
        cout << j+1 << " ";
        stack[j]->printMessage();
    }
}

messageStack::messageStack(){
    i = 0;
    root = NULL;
}

messageStack::~messageStack(){
//    delete[] root;
//    delete[] *stack;
}

void messageStack::push(message original){
    if(root != NULL){
        root = &original;
    }
    if(num < 10){
        stack[i] = new message(original);
        i++;
    }
    else{
        return;
    }
}

void messageStack::push(morseCodeMessage original){
    if(root != NULL){
        root = &original;
    }
    if(num < 10){
        stack[i] = new morseCodeMessage(original);
        i++;
    }
    else{
        return;
    }
}

void messageStack::pop(){
    if(i == 0){
        cout << "The stack is empty" << endl;
        return;
    }
    delete stack[--i];
}

int main(void){
    message message1, message2("Hello");
    morseCodeMessage morseMessage1, morseMessage2;
    messageStack stackMessage1;
    int option = 0;
    //calling 
    cout << "Message 1: " << endl;
    message1.printMessage();
    cout << "Message 2: " << endl;
    message2.printMessage();
    cout << "Message 3: " << endl;
    morseMessage1.printMessage();
    cout << "Message 4: " << endl;
    morseMessage2.printMessage();
    
    while(option != 5){
        cout << "\n1:Push original message\n2:Push translated message\n3:Pop message\n4:Print the stack\n5:End Program" << endl;
        cin >> option;
        if(option == 1){
            stackMessage1.push(message1);
        }
        else if(option == 2){
            stackMessage1.push(morseMessage1);
        }
        else if(option == 3){
            stackMessage1.pop();
        }
        else if(option == 4){
            stackMessage1.printStack();
        }
        else if(option == 5){
            cout << "--Exiting Program--" << endl;
            return 0;
        }
        else{
            cout << "Invalid Option" << endl;
        }
    }
    
    return 0;
}