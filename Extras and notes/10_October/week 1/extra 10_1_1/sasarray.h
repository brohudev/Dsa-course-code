class sasarray
{
private:
    int top; // is an index
    int size;
    int *elt;

public:
    sasarray(int = 10);
    ~sasarray();
    bool isempty();
    bool isfull(); // used because we have static arrays.
    int gettop();

    bool push(int);  // ret -ve if isfull() rets 0
    bool pop(int &); // if !isempty(), go ahead and pop
    void print();
    void removeall();
};