#include <iostream>
using namespace std;

struct pearl{ // structure of an individual pearl in a necklace.
              //has a color in a bead and a hole that points to the next bead
    int color;
    pearl *hole;
};
class Necklace{
    private:
        pearl *head;
        pearl *tail;
    public:
            Necklace(){head=nullptr; tail=nullptr;}
        void addpearl(int c){};
        void print(){};
};
int main(){

    Necklace mine;
    mine.addpearl(1);
    mine.addpearl(5);
    mine.print();

    return 0;
}