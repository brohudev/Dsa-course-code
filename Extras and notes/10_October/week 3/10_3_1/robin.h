#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
struct node{
    string job;
    int totmin;
    int remmin;
    node *next;
};
class robin{
    private:
        node *front;
        node *back;
    public:
        robin();
        bool isempty();
        
        void enqueue(string, int, int);
        void dequeue(); //just cout the current procss in line.
            //always dequeue from the front. front into temp. front ->next, cout temp, delete temp.
        void print();
};