#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include <queue>
using namespace std;
int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}
struct node {
	int data;
	node* left;
	node* right;
	int height;
	node(int d) {
		data = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};
class avlTree {
	private:
		node* root;
	public:
		avlTree() { root = nullptr; }
		void add(int data) { root = insert(root, data); }
		node* getRoot() { return root; }
		node* insert(node* t, int x) {
			if (t == nullptr)
				t = new node(x);
			else if (x < t->data) {
				t->left = insert(t->left, x);
				if (bFactor(t) == 2) {
					if (x < t->left->data)
						t = singleRight(t);
					else
						t = leftRight(t);
				}
			}
			else if (x > t->data) {
				t->right = insert(t->right, x);
				if (bFactor(t) == -2) {
					if (x > t->right->data)
						t = singleLeft(t);
					else
						t = rightLeft(t);
				}
			}
			t->height = max(height(t->left), height(t->right)) + 1;
			return t;
		}
		node* singleRight(node* t) {
			node* u = t->left;
			t->left = u->right;
			u->right = t;
			t->height = max(height(t->left), height(t->right)) + 1;
			u->height = max(height(u->left), height(u->right)) + 1;
			return u;
		}
		node* singleLeft(node* t) {
			node* u = t->right;
			t->right = u->left;
			u->left = t;
			t->height = max(height(t->left), height(t->right)) + 1;
			u->height = max(height(u->left), height(u->right)) + 1;
			return u;
		}
		node* leftRight(node* t) {
			t->left = singleLeft(t->left);
			return singleRight(t);
		}
		node* rightLeft(node* t) {
			t->right = singleRight(t->right);
			return singleLeft(t);		
		}
		int height(node* cu) {
			if (cu == nullptr)
				return -1;
			else
				return cu->height;
		}
		int bFactor(node* cu) {
			return (height(cu->left) - height(cu->right));
		}
		void print(ofstream &output, int numnodes){
			queue<node*> q;
			node *temp = getRoot();
			for(int i=0; i<numnodes;i++){
				output << to_string(temp->data)<<" ";
				if(temp->left != nullptr){
					q.push(temp->left);
				}
				if(temp->right != nullptr){
					q.push(temp->right);
				}
				if(!q.empty())
					temp = q.front(); q.pop();
			}
		}
};

int main(int argc, char* argv[]){
     ArgumentManager am(argc,argv);
     ifstream input(am.get("input"));
     ofstream output(am.get("output"));
     // ifstream input("input2.txt");
     // ofstream output("output2.txt");
     string instr;
     avlTree tree;
	string tempvar;
	getline(input,tempvar);
     while(getline(input, instr)){
         tree.add(stoi(instr));  
     }
	cout << "---------------------printing avl tree"<<endl;
	tree.print(output, stoi(tempvar));
     return 0;
}