#ifndef ID_STACK
#define ID_STACK
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct iD {
    iD * next;
    string data;
    bool isGuilty;
};

class iDStack {
    private:
        int size;
        iD * top;
        
    public:
        iDStack();

        iD* getTop();
        int getSize();

        bool isEmpty();
        bool isFull();

        bool push(string, bool);
        bool pop(string&, iD *, iD *);
        
        int idSearch(iD *, string);
        void idReset(iD *, string);
        string removeLeadZeros(string);
        bool stringComparison(string, string, bool);
        bool isSorted(iD *, bool);
        void swap(iD *, iD * );
        void sortAsc(iD *, iD *, bool);
        void print(iD *, ofstream&, bool, bool, bool);
};

#endif