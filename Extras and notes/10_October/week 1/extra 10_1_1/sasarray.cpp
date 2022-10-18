#include "sasarray.h"

bool sasarray::pop(int &k)
{
    if (!isempty())
    {
        k = elt[top];
        top--;
        return true;
    }
    return false;
};