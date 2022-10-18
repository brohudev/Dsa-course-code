#include <iostream>
#include <string>
using namespace std;
struct node
{
    string data;
    node *next;
    bool guilty;
};
class linkedlist
{
    linkedlist();
    ~linkedlist();
    addatend();
    removeatend();
    print()    // will need to call sort internally
        sort() // prolly need swap if we doin bubble sort.
};