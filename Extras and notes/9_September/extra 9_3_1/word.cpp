#include "word.h"

void word::addatend(char x){
    //create
    letter *temp =new letter;
    //fill in tmep
    temp->l = x;
    temp->next = nullptr;
    //location and update pointer.
    if(head == 0){head = tail = temp;}
    else{
        tail->next = temp;
        tail = tail->next;
    }

}

void word::deletefrombeg(){
    //mark
    letter *temp=head;
    //empty
    cout << "deleting:... "<<temp->l<<endl;
    //update.
    head = head->next; //shift head one node down.
    delete temp; //delete the previous head(now temp)

}

void word::deleteatend(){
    //mark
    letter *temp=tail;
    //empty
    cout << "deleting:... "<<temp->l<<endl;
    //trverse the array using a cu pointer.
    letter *cu = head;
    //stop before tail. so when cu->next = tail
    while(cu->next!=tail){
        cu = cu->next;
    }
    //delete tail
    //set cu->next to nullptr
    cu->next = nullptr; //tail address is stored in temp. safe to do this.
    //set cu to tail(so now the tail goes up one node)
    tail = cu;
    delete temp; //get ride of the previous tail(now stored under temp)
}

void word::print(){
    letter *cu = head;
    while(cu != nullptr){
        cout << cu->l << endl;
        cu = cu->next;
    }
}

void word::printrec(letter *cu){//print and traverse the linked lsit recursively
    if(cu==nullptr){
        return;
    }
    else{
        cout <<cu->l<<endl;
        printrec(cu->next);
    }
}