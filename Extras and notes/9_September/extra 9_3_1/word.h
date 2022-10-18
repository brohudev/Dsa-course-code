#include <iostream>
using namespace std;

struct letter{
    char l;
    letter *next;
};

class word{
    private:
        letter *head;
        letter *tail;
    public:
        word(){head = tail = 0;}
        void addatend(char);
        void deletefrombeg();
        void print();
        void deleteatend();
        void printrec(letter *);
};