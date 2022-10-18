// all about templates
// typename and class are synomous for now. typename is used when more than one program are using the same template, class is local
//? oct4_stack is the replit for this day.
//! the goal is to change the stack to a template.
#include <iostream>
#include "sasarray.h"
using namespace std;
int main()
{
    int k = 0;
    sasarray<int> s1;
    sasarray<int> s2(5);
    s1.push(58);
    s2.push(1);
    s2.pop(k); // will pass the address of k (oass by reference)
               // where pop will store the top off the stack
    cout << "the current top has been moved from s2 into k: " << k << endl;
    s2.push(17);
    s2.removeall();
    return 0;
}