#include <iostream>

using namespace std;
struct student{
    int age;
    float gpa;
};
int main(){
    student eric;
    eric.age = 20;
    eric.gpa = 4.0;
    
    student *p=new student;
    p->age=19;
    p->gpa=30;

    //a dynamic array of students
    student *q = new student[3];  //q starts off pointing to the beginning of the array.
    q->age=19; 
    q->gpa=2.5;

    q++; //is now pointing to the second cell in the array. each cell also has two fields. so this operation does not move the field
    //we can access th field by directly naming it through the arrow.
    q->age=21;
    q->gpa=3.1;
   
    q++;
    q->age=22;
    q->gpa=3.2;
     return 0;
}