#include "sasll.h"
bool sasll::push(int k)
{
    node *temp = new node;
    if (temp == nullptr)
        return false;
    // same as assert(temp). checks if temp has
    // been allocated to the stack

    temp->nb = k;
    temp->next = nullptr;

    temp->next = top;
    top = temp;
};