#include <string>
#include <iostream>
using namespace std;
struct node
{
    node *next;
    node *prev;
    string data;
    bool isopr; // is an operand flag
};
class expression{
private:
    node *exphead;
    double answer;
    string exp;
public:
    expression();
    ~expression();
    
    //* lab specific methods:
    string infixtopostfix(string);
    bool evalpostfix(string);
    int priorityof(char);
    bool assignopr(string);
    int isop(string); //1 = operand; 2=operstor; 3=brackets.
    int prec(char); //returns the precedence of the operator, including braces
    
    //*run of th mill stuff
    void print(); //! implement
    bool isempty();
    string getexp();
};