struct node
{
    int nb;
    node *next;
};

class sasll
{
private:
    node *top;

public:
    sasll();
    bool isempty();
    bool push(int);
    bool pop(int &);
    void print();
    void removeall();
};