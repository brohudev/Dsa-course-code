#include <iostream>
#include "listofcars.h"

using namespace std;

listofcars::listofcars(){
    head=nullptr;
}

bool listofcars::isempty(){
    if(head==nullptr)
        return true;
    else
        return false;
}

void listofcars::addatbeg(int a, float b){
    //create a car
    if(isempty()){//first node in the list:-
        head = new car;
        head->year = a;
        head->price = b;
        head->next=nullptr;
    }
    else{//not first node in the list:-
        car *temp = new car; //creates a node to be pushed to the front. 
        temp->year = a;//fill in details
        temp->price = b;
        temp->next = nullptr;
        temp->next = head;//link it with the previous head.
        head = temp;//make it eh new head.

        //!everytime you create a new car. it looks at the first car on the chain, and makes the newly created temp car the first car, pushing the previous one down the chain. the list gets uppended on the front rather than the back. 
    }

    
}

void listofcars::addatend(int a, float b){
    if(isempty()){//first node in the list:-
        head = new car;
        head->year = a;
        head->price = b;
        head->next=nullptr;
    }
    else{//not first node in the list:-
        car *temp = new car; //creates a node to be pushed to the front. 
        temp->year = a;//fill in details
        temp->price = b;
        temp->next = nullptr;
        car *cu=head;
    //traverse the list until you hit the last node
    while(cu!=nullptr){
        cu = cu->next;
    }
    cu->next=temp;

        //!everytime you create a new car. it looks at the first car on the chain, and goes to the end of theat last, at which point cu is at the last node. you then set the cu->next field to temp, adding the temp car to the end of the list, making it one car longer.
     
}
}

void listofcars::addmidval(int a, float b, int value){
    car *temp = new car;
    temp->year = a;
    temp->price = b;
    temp->next = nullptr;
    car *cu = head;
    while(cu->year != value)
    {
        cu = cu->next;
    }
    temp->next = cu->next;
    cu->next = temp;

}

void listofcars::addmidpos(int a, float b, int pos){
    car *temp = new car;
    temp->year = a;
    temp->price = b;
    temp->next = nullptr;
    car *cu = head;
    for(int i=0; i<(pos-1);i++){
        cu = cu->next;
    }
    temp->next = cu->next;
    cu->next = temp;
}

void listofcars::print(){
    cout << "the car was built in ";
}