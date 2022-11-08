#ifndef QUEUE_H
#define QUEUE_H
#include <fstream>
#include <iostream>
using namespace std;

struct validExpression{
    validExpression * next;
    string expression;
    double value;
};
class Queue{
    private:
        validExpression * front;
        validExpression * back;
        int size;
    public:
        Queue();
        bool isEmpty();
        void enqueue(string, double);
        void dequeue();
        void print(ofstream& );
        validExpression * getFront(){
            return front;
        } 
        double getFrontValue(){
            return front->value;
        }
        string getFrontExpression(){
            return front->expression;
        }
        int getSize(){
            return size;
        }
};

Queue::Queue(){
    front = nullptr;
    back = nullptr;
    size = 0;
}

bool Queue::isEmpty(){
    if (front == nullptr){
        return true;
    }
    else{
        return false;
    }
}
void Queue::enqueue(string exp, double val){
    validExpression * temp = new validExpression;
    temp->expression = exp;
    temp->value = val;
    temp->next = nullptr;

    if(isEmpty()){
        front = temp;
        back = temp;
        size++;
    }
    else{
        back->next = temp;
        back = temp;
        size++;
    }
}
void Queue::dequeue(){
    validExpression * mark = front;
    front = front -> next;
    delete mark;
    size--;
    return;
}
void Queue::print(ofstream& out){
    validExpression * current = front;
    if (front == nullptr) {
        cout << "No Valid Expression"; // DELETE
        out << "No Valid Expression";
        return;
    }
    while(current != nullptr){
        if(current == back){
            out << current->expression;
            cout << current->expression << " : " << current->value; // DELLETE
        }
        else{
            out << current->expression << endl;
            cout << current->expression << " : " << current->value << endl; // DELETE
        }
        current = current->next;
    }
}

#endif