#include <iostream>
#include "listofcars.h"
using namespace std;

int main(){
    listofcars lexus;
    lexus.addatbeg(1950,100);
    lexus.addatbeg(2020,50.7);
    lexus.addatend(2021,101);
    lexus.addmidval(2022,800,2021);

    return 0;
}