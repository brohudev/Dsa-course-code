#include <iostream>
#include <sstream>
using namespace std;

struct cred{
    string data;
    cred *next;
};

class listofcredentials{
    private:
        cred *head;
        cred *tail;
        int size;
    public:
        listofcredentials(){head = tail = nullptr; size = 0;};
        void addatpos(string, int pos);
        void addatend(string);
        void deletefrombeg();
        void deletepos(int pos);
        string print();
        void deleteatend();
        bool isvalid(string);
};