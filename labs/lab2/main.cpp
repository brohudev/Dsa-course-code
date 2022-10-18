#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
#include <typeinfo>
#include <sstream>
using namespace std;
template <typename T>//watch a tutorial about templates in cpp
struct node{ T data; node<T> *next; };
template <typename T>
class linkedlist {
    private:
        node<T> *head;
        int size;
    public:
        linkedlist();//constructor
        ~linkedlist();//call when your code ends, the destructor
        string print(string);
        void addatbeg(T);
        void removeatbeg();
        void addatend(T);
        void removeatend();
        bool isempty(){ return head == nullptr; };
        int getsize(){ return size;};
        void sort();
        void swap(node<T>*, node<T>*);
};
template <typename T>//the constructor
linkedlist<T>::linkedlist(){
    head = nullptr;
    size = 0;
    cout << "constructor called"<<endl;
};
template <typename T>
void linkedlist<T>::swap(node<T>* cu, node<T>* prev){

};
template <typename T>
void linkedlist<T>::addatbeg(T value){
    node<T> *temp = new node<T>();  //new temp node and store values
    temp ->data = value;
    temp -> next = nullptr;
    if(isempty()){ head =temp; }
    else{ temp->next = head; head = temp; }
    size++;
};
template <typename T>
void linkedlist<T>::sort(){
    node<T>* cu = new node<T>();
    node<T>* prev = new node<T>();
    int swapp = 1;
    while(swapp){
            swap = 0;
            cu = head->next;
            prev = head;
            while(cu!=nullptr){
                if(cu->data < prev->data){
                    swap(cu, prev);
                    swapp = 1;
                }
                prev = cu;
                cu = cu->next;
            }
    }
};
template <typename T>
void linkedlist<T>::addatend(T value){
    node<T> *temp = new node<T>();  //new temp node and store values
    temp ->data = value;
    temp -> next = nullptr;
    if(head == nullptr){ head = temp; }  //first node in the array, set both head and tail as temp
    else{ 
        node<T>* cu = head;
        while(cu->next != nullptr){cu = cu->next;}
        cu->next = temp;
     }
    size++;

};
template <typename T>
void linkedlist<T>::removeatbeg(){
    node<T> *temp = head;//mark the current head to temp for deleting
    head = head->next;//move head one node down
    delete temp;
    temp = nullptr;
    size--;
}
template <typename T>
void linkedlist<T>::removeatend(){
    node<T> *cu = head;
    node<T> *prev = nullptr;
    if(cu==nullptr){ return; }
    else if(size == 1){delete cu, prev; head = nullptr;}
    else{//more than one node
        while (cu->next != nullptr){
            prev = cu; //move the previous node up by one
            cu = cu->next; //move onto the next node
        }
        prev ->next = nullptr;
        delete cu;
        cu = nullptr;
    }
    size--;
};
template <typename T>
string linkedlist<T>::print(string ltype){
    node<T> *cu = head;
    stringstream ss;
    while (cu != nullptr){
        ss << cu->data;
        cout << "printing " << cu-> data<<endl;
        if(cu->next != nullptr){ss << " ";}
        cu = cu->next;
    }
    return ss.str();   
};
template <typename T>//the destructor
linkedlist<T>::~linkedlist(){
    cout << "destructor called" <<endl;
    node<T> *cu = head;
    while(cu!= nullptr){
        node<T> *temp = cu;
        cu = cu->next;
        delete temp;
    }
}
int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream out(am.get("output"));
    linkedlist<int> intlist;
    linkedlist<string> strlist;
    linkedlist<char> charlist;
    ifstream input("input3.txt");
    ofstream out("output3.txt");
    string in = "";
    string ltype = "";
    string addat = "";
    int ct = 1;
    if(input.peek() != EOF){//takes care of the empty file case.
        while(getline(input, in)) {
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            cout << in << endl;
            if(in.size() == 0){ continue; }
            if(ct<=2){
                if(in == "string"){ ltype = "s"; }
                else if(in == "int"){ ltype = "i"; }
                else if(in == "char"){ ltype = "c"; }
                else if(in == "head"){ addat = "head";}
                else if(in == "tail"){ addat = "tail";}
            }
            else{
                if(in == "remove tail"){
                    if(ltype == "s"){strlist.removeatend();}
                    else if(ltype == "i"){intlist.removeatend();}
                    else if(ltype == "c"){charlist.removeatend();}
                }
                else if(in == "remove head"){
                    if(ltype == "s"){strlist.removeatbeg();}
                    else if(ltype == "i"){intlist.removeatbeg();}
                    else if(ltype == "c"){charlist.removeatbeg();}
                }
                else if(ltype == "s"){
                    if(addat == "head"){ strlist.addatbeg(in);}
                    else{ strlist.addatend(in);}
                }
                else if(ltype == "i"){
                    if(addat == "head"){ intlist.addatbeg(stoi(in)); }
                    else{ intlist.addatend(stoi(in)); }
                }
                else if(ltype == "c"){
                            if(addat == "head"){ charlist.addatbeg(in[0]); }
                            else{ charlist.addatend(in[0]); }
                    }
                }  
            ct++;
            }
    }
    if(ltype == "s"){out << strlist.print(ltype);}
    if(ltype == "i"){out << intlist.print(ltype);}
    if(ltype == "c"){out << charlist.print(ltype);}
    return 0;//calls the destructor when return hits.
}
