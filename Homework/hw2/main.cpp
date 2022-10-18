#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include "listofcredentials.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
//    ifstream input(am.get("input"));
//    ifstream command(am.get("command"));
//    ofstream out(am.get("output"));

  ifstream input("input3.txt");
  ifstream command("command3.txt");
  ofstream out("output3.txt");
  
  string in = "";   
  string temp = "";
  listofcredentials list; 

   while(getline(input, in)) {
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    if(in.size() == 0){ continue; }
    list.addatend(in);
   }
}
//template <typename T>//for hw1. dont need templates for that. but hes building it with one just to screw with us
/*void linkedlist<T>::addatpos(T value, int pos){
    node<T> *temp= new node<T>();
    temp->data = value;
    temp->next = nullptr;

    node<T> *cu = head;
    node<T> *prev = nullptr;

    if(pos >size){ return; }//this function will also check whether or not the list is null.
    else if(pos == 0){//at at the beginning of the list 
        head = temp;    //sets temp as teh head node. but temp->next stilldoesnt point to the last head
        temp->next = cu;//so make temp->next point to the prev head node.
    }
    else{//this is somewhere in the middle of the lsit
        for (int i = 0; i < pos; i++)//better when you know the pos to travel to
        {
            prev = cu;
            cu = cu->next;
        }
        prev->next = temp;//puts temp after the previous node
        temp-> next = cu; //puts 

        
    }

};
*/