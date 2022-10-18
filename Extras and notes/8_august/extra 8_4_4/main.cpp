# include <iostream>

using namespace std;
 int main(){
    //static stuff
    int a = 10;
    cout << "slow " << a;

    int *p = &a;
    cout << "fast " << *p;
    cout << " address " << p;

    //dynamic memory
    p = new int;
    *p = 10;
    cout << *p;
    delete p;
    p=nullptr;
    p = new int[4];
    for (int i=0; i<4; i++){
        p[i] = i*10;
    }
    for (int i = 0; i<4; i++){
        cout << *p << endl;
        p++;
    }
    cout<<*p;
    p-=3;
    cout<<*p;
 }