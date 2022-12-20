#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <queue>
#include<iterator>
#include <algorithm>
#include <map>
using namespace std;
class TreeNode {
  int *keys;
  int t;
  TreeNode **C;
  int n;
  bool leaf;

   public:
  TreeNode(int temp, bool bool_leaf);
  void insertNonFull(int k);
  void splitChild(int i, TreeNode *y);
  void height(TreeNode*temp,int height, int& result);
  friend class BTree;
  void traverse(int level);
  void printLevel(TreeNode*temp,int level,ofstream& fout);

};
class BTree {
     TreeNode *root;
     int t;
     public:
     BTree(int temp) {
     root = NULL;
     t = temp;
     }
     void insert(int k);
     int height(){
          int result;
          root->height(root,1, result);
          return result;
     }
     void traverse() {
          if (root != NULL)
               root->traverse(1);
     }
     void printLevel(int level,ofstream &fout){
          int levelcounter =1;
          queue<TreeNode*> q;
          q.push(root);
          cout << root->keys[1]<<endl;
          TreeNode* delimiter = new TreeNode(t, false); delimiter->keys[0]= -1; q.push(delimiter);
          while(levelcounter != level){
               while(q.front()->keys[0] != -1){ // while you havent hit the delimiter
                    TreeNode* temp = q.front();q.pop();
                    for(int i = 0; i<temp->n;i++){//push all the kids of temp into the queue.
                         cout << temp->keys[0]<<endl;
                         q.push(temp->C[i]);
                    }
               }
               q.pop();// ? done correctly the front should be the delimiter.
               q.push(delimiter); //signals the end of the next level.
               levelcounter++;
          }
          while(q.front()->keys[0] != -1){
               for(int i=0; i<(q.front()->n); i++){ //the node will hold t-1 keys and i need them all to cout.
                    cout <<q.front()->keys[i]<<" ";
               }
               q.pop();
          }
          q.pop(); //remove the final delimiter.
          // root->printLevel(root,level,fout);
     }
};
void TreeNode::traverse(int level) {
  int i;
  for (i = 0; i < n; i++) {//for every child of the current node(starting as root):
    if (leaf == false && level != 1)//if the node is not at the desired level, go deeper.
      C[i]->traverse(level-1);
    else  //otherwise we found our boi print it.
     cout << " " << keys[i];
  }
  if (leaf == false && level != 1)//cover the rightmost child
    C[i]->traverse(level-1);
}
void TreeNode::height(TreeNode* temp, int h, int& result){
     if(leaf){
                result=h;
                return;  
            }
            C[0]->height(temp,h+1,result);
}
TreeNode::TreeNode(int t1, bool leaf1) {
  t = t1;
  leaf = leaf1;
  keys = new int[2 * t - 1];
  C = new TreeNode *[2 * t];
  n = 0;
}
void BTree::insert(int k) {
  if (root == NULL) {
    root = new TreeNode(t, true);
    root->keys[0] = k;
    root->n = 1;
  } else {
    if (root->n == 2 * t - 1) {
      TreeNode *s = new TreeNode(t, false);
      s->C[0] = root;
      s->splitChild(0, root);
      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k);
      root = s;
    } else
      root->insertNonFull(k);
  }
}
void TreeNode::insertNonFull(int k) {
  int i = n - 1;
  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      i--;
    }
    keys[i + 1] = k;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;
    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);
      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k);
  }
}
void TreeNode::splitChild(int i, TreeNode *y) {
  TreeNode *z = new TreeNode(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
    z->keys[j] = y->keys[j + t];

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[t - 1];
  n = n + 1;
}
void TreeNode::printLevel(TreeNode*temp,int level,ofstream &out){
         if(level>1 && leaf){
             return;
         }
         else if(level==1){
             for(int i=0;i<n;i++){
                 cout<<keys[i]<<" ";
             }
         }
         else{
             for(int i=0;i<=n;i++){
                 C[i]->printLevel(temp,level-1,out);
             }
         }
}
int main(int argc, char* argv[]) {
     ArgumentManager am(argc,argv);
     ifstream input("input3.txt");
     ifstream command("command3.txt");
     ofstream out("output1.txt");
     string instr; int height,level;
     command >> instr;
     cout <<instr<<endl;
     instr = instr.substr(instr.find("=")+1);
     BTree tree(stoi(instr));
     map<int,int> bucket;
     while(input >> instr){
          if(instr.empty())
               continue;
          // Clean up blank spaces, \n and \r, and skip blank lines
          instr.erase(remove(instr.begin(), instr.end(), '\n'), instr.end());
          instr.erase(remove(instr.begin(), instr.end(), '\r'), instr.end());
          if(!bucket.count(stoi(instr))){ // checks for duplicates against a map of keys
               tree.insert(stoi(instr));
               bucket[stoi(instr)]=1;
          } 
     }
     tree.traverse(1);
     height = tree.height()+1;//get the height, but there is a bug where its offset by one.
     cout<<"-------------------------------output from here on"<<endl;
     cout <<"height "<<height<<endl;
     while(getline(command,instr)){ // dump onto the output.
          if(instr.empty())
               continue;
          cout <<instr<<endl;
          instr = instr.substr(instr.find_last_of("l")+2);
          level = stoi(instr);
          tree.printLevel(1,out);
          // if(level>(tree.height()+1))
          //      cout<<"Empty";
          // else
          //      tree.printLevel(level,out);
          // cout << "\n"<<endl;
     }
     return 0;
}