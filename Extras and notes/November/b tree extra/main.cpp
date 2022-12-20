#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;
struct node{
     int *keys;
     node **childptr;
     bool leaf;
     int size;
     node(int degree){
          keys = new int[degree];
          childptr = new node*[degree +1];
          leaf = true;
          size = 0;
          for(int i =0; i<degree; i++){
               keys[i] = -1;
          }
          // for degree = smth. get this __has_is_transparent

     }
     
};
class btree{
     private:
          node* root;
          int degree;
     public:
          btree(int _degree){
               root = nullptr;
               degree = _degree;
          };
          void insert(int data){
               if(root == nullptr){
                    root = new node(degree);
                    root->keys[0] = data;
                    root->size +=1;
               }
               else{
                    addatleaf(nullptr, root, data);
               }
               
          };
          void addatleaf(node* parent, node* n, int data){
               if(n->leaf){
                    int i = n->size;
                    while(i != 0 && n->keys[i-1] == data){
                         n->keys[i] = n->keys[i-1];
                         i--;
                    }
                    n->keys[i]= data;
                    n->size +=1;
               }          
               else{
                    int i = 0;
                    while(i <n->size && data > n->keys[i]){
                         i++;
                    }

               }
               if(n->size == degree){
                    if(n == root){
                         node* temp = new node(degree);
                         temp->leaf = false;
                         temp->childptr[0] = n;
                         splitchild(temp, n);
                         root = temp;
                    }
               }
          }
          void splitchild(node* parent, node* leftnode){
               node* rightnode = new node(degree);
               int mid = (degree -1)/2;

               //* copy half of the kep from the left node to the right node;
               
               // * check if the node youre splitting is a leaf node; if not, cope half the pointers from left node to right node
               // * find the correct index to add the right node;
               // * add the middle key the to parent
               // * 
          }
};
int main(int argc, char* argv[]){
     ArgumentManager am(argc,argv);
     //ifstream input(am.get("input"));
     //ifstream command(am.get("command"));
     //ofstream out(am.get("output"));
     ifstream input("input1.txt");
     ifstream command("command1.txt");
     ofstream out("output1.txt");
     string inStr;
     
     return 0;
}