#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include <stack>
using namespace std;

//!need to implement. rn i have it to true always.
bool isvalidparenthesis(string inStr){
     return true;
}
//!does not account for {} and []
string infixtopostfix(string input){
     return input;
}
//!does not account for {} and []
double evalpostfix(string input){
     return 0.0;
}
struct node{
     string equation;
     double priority;
     node *next;
};
class queue{
     private:
          node *head;
          node *tail;
          //int size; //idk why. might need it.
     public:
          queue() { head = tail = nullptr; };
          ~queue();
          void push(string, double); //inserts based on double. lower values up front.
          node* pop(); //returns the entire node at the head.
          bool isempty(){ return head == nullptr;}
          void print(ofstream&);

};
queue::~queue(){
     node* cu = head;
     while(head != nullptr){
          head = head->next; //move head to next element
          delete cu;//delete current head
          cu = head; //set the new head as current. for next iteration
     }
};
void queue::push(string equation, double priority){
     node* temp; //make a new node
     temp->equation = equation;
     temp->priority = priority;
     temp->next = nullptr;
     node *cu = head;
     //todo case where queue is empty
     //todo case where there is one node in the queue. idk if the while loop will implode
     while (priority >= cu->priority){ //smaller priority first. so if prio < cu->prio we found the right place.
          head = head ->next; //move head away from the battle
          cu->next = nullptr;//break the link to head.
          tail->next = cu;//move cu to last in queue. 
          tail = tail->next; //otherwise tail'd get buried in the middle somewhere.
          cu = head; //iterator condition.
     }
     temp->next = head; //place it fron of the queue
     head = temp; //move head one back.
     
     cu = head;//redundancy.
     while(cu->priority <= cu->next->priority){//sorted correctly, cu > next means cu is the last node in the array and next the first.
          head = head ->next; //move head away from the battle
          cu->next = nullptr;//break the link to head.
          tail->next = cu;//move cu to last in queue. 
          tail = tail->next; //otherwise tail'd get buried in the middle somewhere.
          cu = head; //iterator condition.
     }
};
void queue::print(ofstream &out){

};

int main(int argc, char* argv[]){
     ArgumentManager am(argc,argv);
     //ifstream input(am.get("input"));
     //ifstream command(am.get("command"));
     //ofstream out(am.get("output"));
     ifstream input("input1.txt");
     ifstream command("command1.txt");
     ofstream output("output1.txt");
     string inStr;
     queue q;
     while(getline(input, inStr)){
          inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
          inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
          inStr.erase(remove(inStr.begin(), inStr.end(), ' '), inStr.end());
          if(inStr.empty())
               continue;
          cout << inStr<<endl;
          double priority;
          if(isvalidparenthesis(inStr)){
               priority = evalpostfix(infixtopostfix(inStr)); //get priority of instr
               q.push(inStr, priority);
          }
     }

     return 0;
}