template <typename T>
class sasarray
{
private:
    int top; // is an index
    int size;
    T *elt;

public:
    sasarray(int = 10);
    ~sasarray();
    bool isempty();
    bool isfull(); // used because we have static arrays.
    T gettop();

    bool push(T);  // ret -ve if isfull() rets 0
    bool pop(T &); // if !isempty(), go ahead and pop
    void print();
    void removeall();
};