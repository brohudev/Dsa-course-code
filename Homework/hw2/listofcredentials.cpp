#include <string>
#include "listofcredentials.h"

void listofcredentials::addatpos(string data, int pos){
    cred *temp= new cred();
    temp->data= data;
    temp->next = nullptr;

    cred *cu = head;
    cred *prev = nullptr;

    if(pos >size){ return; }//null & outofbound check
    else if(pos == 0 && isvalid(data)){//add at the beginning of the list 
        head = temp;    //sets temp as teh head node. but temp->next stilldoesnt point to the last head
        temp->next = cu;//so make temp->next point to the prev head node.
    }
    else if(isvalid(data)){//this is somewhere in the middle of the lsit
        for (int i = 0; i < pos; i++)//better when you know the pos to travel to
        {
            prev = cu;
            cu = cu->next;
        }
        prev->next = temp;//puts temp after the previous node
        temp-> next = cu; //puts 

        
    }

}

void listofcredentials::addatend(string in){
    cred *temp = new cred;
    temp->data = in;
    temp->next = nullptr;

    cout <<"addatend: "<< in << endl;
    if(isvalid(in)){
        cout << "^adding^";
        if(head = nullptr){ head = temp;tail = temp; cout << head->data<<endl; }
        else{tail->next = temp; //add temp on to the tail
             tail = tail->next; //move tail one pos down.
             cout << tail->data << endl;
        }
    }
    
}

void listofcredentials::deletefrombeg(){

}

void listofcredentials::deletepos(int pos){}

string listofcredentials::print(){
    cred *cu = head;
    stringstream ss;
    while (cu != nullptr){
        ss << cu->data;
        cout << "printing " << cu-> data<<endl;
        cu = cu->next;
    }
    return ss.str();
}

void listofcredentials::deleteatend(){

}