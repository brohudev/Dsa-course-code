#include <iostream>
using namespace std;

struct car{
    int year;
    float price;
    car *next;
};

class listofcars{
    private:
        car *head;
    public:
        listofcars();
        bool isempty();
        void addatbeg(int, float);
        void addatend(int, float);
        void addmidval(int, float, int value);
        void addmidpos(int, float, int pos);
        //void delete();
        //void search();
        void print();
};