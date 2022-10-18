#include <iostream>
using namespace std;
int p(int n){
    if (n==0)
        return 0;
    else{
        p(n-1);
        cout << n;
    }
}
int add(int n){
    if (n==1)
        return 1;
    else{
        return (n+add(n-1));
    }
}
int main (){
    cout << add(3);
    return 0;
}