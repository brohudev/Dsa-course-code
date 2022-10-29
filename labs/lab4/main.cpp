#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

struct node{
    double priority;
    string task;
    node* next;
};
class pqueue{
    private:
        node* head;
    public:
        pqueue();//done
        ~pqueue();//done
        void push(string, double);//done
        void pushend(node*);//done
        double top(); //done //only need priority of the top node for comparison.
        string toptask();//done
        node* pop();//done
        void print(ofstream &);//done
        void print(); //done
};
pqueue::pqueue(){head = nullptr;};
pqueue::~pqueue(){
    while(head != nullptr){
        node *temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
};
void pqueue::print(){
    while(head != nullptr){
        if(head->next !=nullptr)//takes care of teh extra line issue
            cout << head->task <<endl;
        else
            cout <<head->task;
        delete pop();//have to iterate the head. efficient use.
    }
};
void pqueue::print(ofstream &out){
    while(head != nullptr){
        if(head->next !=nullptr)//takes care of teh extra line issue
            out << head->task <<endl;
        else
            out <<head->task;
        delete pop();//have to iterate the head. efficient use.
    }
};
void pqueue::push(string task, double priority){
    node *temp = new node;
    temp->task = task;
    temp->priority = priority;
    temp->next = nullptr;

    if (head == nullptr)
        head = temp;
    else {
        node *cu = head;
        node *prev = nullptr;
        if (temp->priority < cu->priority) {//task is first in line.
        temp->next = head;
        head = temp;
        }
        else {
        while (cu != nullptr && temp->priority >= cu->priority) {
            prev = cu;
            cu = cu->next;
        }
        prev->next = temp;
        temp->next = cu;
        }
    }
    
};

void pqueue::pushend(node* temp){
    node *cu = head;
    while(cu->next !=nullptr)
        cu=cu->next; //slightly illegal tailfinder for queue
    cu->next = temp;
};
double pqueue::top(){
    return head->priority;
};
string pqueue::toptask(){
    return head->task;
}
node* pqueue::pop(){
    node *temp = head; //store current head
    if(head !=nullptr)//also tkes cre of nullptr head. since temp is also null, and saves a seg fault.
        head = head->next; //move head one down, 
    return temp;
}

int main(int argc, char* argv[]){
    ArgumentManager am(argc,argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));
    // ifstream input("input3.txt");
    // ofstream out("output1.txt");
    string inStr;
    pqueue queue;
    while(getline(input, inStr)){//input every thing into a priorityqueue
        cout <<inStr<<endl;
        double priority = stod(inStr.substr(inStr.find_last_of(" ")+1));
        cout <<priority<<endl;
        inStr = inStr.substr(0,inStr.find_last_of(" "));
        queue.push(inStr, priority);        
    }
    // queue.print();
    queue.print(out);
    return 0;
}