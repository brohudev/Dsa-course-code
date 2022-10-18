#include "sasarray.h"
template <typename T>
bool sasarray<T>::pop(T &k)
{
    if (!isempty())
    {
        k = elt[top];
        top--;
        return true;
    }
    return false;
};

template <typename T>
bool sasarray<T>::push(T k){};
