#include <iostream>
#include "sasarray.h"
using namespace std;
//! just plain implementation of a stackarray class
int main()
{
    int k = 0;
    sasarray s1;
    sasarray s2(5);
    s1.push(58);
    s2.push(1);
    s2.pop(k); // will pass the address of k (oass by reference)
               // where pop will store the top off the stack
    cout << "the current top has been moved from s2 into k: " << k << endl;
    s2.push(17);
    s2.removeall();
    return 0;
}