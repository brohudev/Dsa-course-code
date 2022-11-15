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
	string data;
	node* left;
	node* right;
	int height;
	node(string d) {
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
        void add(string data) { root = insert(root, data); }
        node* getRoot() { return root; }
        node* insert(node* t, string x) {
            if (t == nullptr)
                t = new node(x);
            else if (x.length() < t->data.length()) {
                t->left = insert(t->left, x);
                if (bFactor(t) == 2) {
                    if (x.length() < t->left->data.length())
                        t = singleRight(t);
                    else
                        t = leftRight(t);
                }
            }
            else if (x.length() > t->data.length()) {
                t->right = insert(t->right, x);
                if (bFactor(t) == -2) {
                    if (x.length() > t->right->data.length())
                        t = singleLeft(t);
                    else
                        t = rightLeft(t);
                }
            }
            else
                t->data = x; //when the length of input matches curr node, replace it. nothing else changes.
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
        int bFactor(node* cu) { return (height(cu->left) - height(cu->right)); }
        void print(ofstream &out, node* parent, int c){
            if (parent != nullptr) {
                if(c==2){
                    out << parent->data <<endl;
                }
                print(out,parent->left,c);
                if(c==1){
                    out << parent->data<<endl;
                }
                print(out,parent->right,c);
                if(c==3){
                    out << parent->data <<endl;
                }
            }
            return;
        }
};

struct prionode{
    double priority;
    string task;
    prionode* next;
};
class pqueue{
    private:
        prionode* head;
    public:
        pqueue();//done
        ~pqueue();//done
        void push(string, double);//done
        void pushend(prionode*);//done
        string top();//done
        prionode* pop();//done
        void print(ofstream &);//done
        void print(); //done
        bool empty(){return head == nullptr;};
};
pqueue::pqueue(){head = nullptr;};
pqueue::~pqueue(){
    while(head != nullptr){
        prionode *temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
};
void pqueue::push(string task, double priority){
    prionode *temp = new prionode;
    temp->task = task;
    temp->priority = priority;
    temp->next = nullptr;

    if (head == nullptr)
        head = temp;
    else {
        prionode *cu = head;
        prionode *prev = nullptr;
        if (temp->priority < cu->priority) {//task is first in line.
        temp->next = head;
        head = temp;
        }
        else {
        while (cu != nullptr && temp->priority >= cu->priority) {
            prev = cu;
            cu = cu->next;
        }
        prev->next = temp;
        temp->next = cu;
        }
    }
    
};
void pqueue::pushend(prionode* temp){
    prionode *cu = head;
    while(cu->next !=nullptr)
        cu=cu->next; //slightly illegal tailfinder for queue
    cu->next = temp;
};
string pqueue::top(){
    return head->task;
}
prionode* pqueue::pop(){
    prionode *temp = head; //store current head
    if(head !=nullptr)//also tkes cre of nullptr head. since temp is also null, and saves a seg fault.
        head = head->next; //move head one down, 
    return temp;
}

int main(int argc, char* argv[]){
    ArgumentManager am(argc,argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));
    // ifstream input("input3.txt");
    // ofstream out("output1.txt");
    string msg, arg, arg2, cmd, temp, in, order; //need them strings.
    int prio;
    avlTree tree; pqueue pq; queue<string> q; //bsts and q's
    while(getline(input, msg)){
        if(msg.empty())
            continue;   
        if(msg == "Inorder" || msg == "Postorder" || msg == "Preorder"){ order = msg; break;}
        prio = stoi(msg.substr(msg.find_last_of("(")+1,(msg.find_last_of(")")-msg.find_last_of("(")-1)));
        msg = msg.substr(0,msg.find_last_of("("));
        pq.push(msg, prio);
    }
    while (!pq.empty()){
        cmd = pq.top().substr(0,pq.top().find(":")); //get the commmand
        in = pq.top().substr(pq.top().find("[")+1, pq.top().length()-pq.top().find("[")-2); //get the meat
        if(cmd == "DECODE"){
            q.push(in); pq.pop(); continue;    //plop it into the regular q
        }
        if(q.empty()){
            pq.pop(); continue; //should take care of the bit where no msg in q and the cmd is not of decode type.
        }
        arg = in.substr(0,in.find(","));//for when i need two args.
        arg2 = in.substr(in.find(",")+1);
        if(cmd == "REPLACE"){
            temp = q.front(); q.pop(); // store the top into temp
            for(int i=0; i<temp.length(); i++){ //replace every arg with arg2
                if(temp[i] == arg[0])
                    temp[i] = arg2[0];
            } q.push(temp);pq.pop(); continue;
        }
        else if(cmd == "ADD"){
            temp = q.front(); q.pop(); // store the top into temp
            for(int i = 0; i < temp.length(); i++){
                if(temp[i] == arg[0]){
                    temp = temp.substr(0,i+1)+arg2+temp.substr(i+1);
                }
            } q.push(temp);pq.pop(); continue;
        }
        else if(cmd == "REMOVE"){
            temp = q.front(); q.pop(); //store the top into temp
            for(int i=0; i<temp.length();i++){
                if(temp[i] == in[0]){
                    temp = temp.substr(0,i) +temp.substr(i+1);
                    i--;
                }
            } q.push(temp);pq.pop(); continue;
        }
        else if(cmd == "SWAP"){
            temp = q.front(); q.pop(); // store the top into temp
            for(int i=0; i<temp.length(); i++){ //replace every arg with arg2
                if(temp[i] == arg[0]){ // every a with b
                    temp[i] = arg2[0]; continue; //otherwise this will double change back to what it was originaly.
                }
                else if(temp[i] == arg2[0]){ //every b with a
                    temp[i] = arg[0]; continue;
                }
            }q.push(temp);pq.pop(); continue;
        }
        else if(cmd == "BST"){
            temp = q.front(); q.pop(); //store the top into temp
            tree.add(temp);
            pq.pop();continue; // once you hit bst, no pushing temp back into q.
        }
    }
    switch(order[1]){
        case 'n': // * if its inorder - 2
            tree.print(out,tree.getRoot(), 1); //print recursive cases.
            break;
        case 'r': // * if its preorder - 2
            tree.print(out,tree.getRoot(), 2); //print recursive cases.
            break;
        case 'o':// * if its postorder - 3
            tree.print(out, tree.getRoot(), 3);
            break;
    }
     return 0;
}