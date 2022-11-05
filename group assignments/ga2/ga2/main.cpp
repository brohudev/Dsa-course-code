#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include <stack>
using namespace std;
int prec(char c) {
  if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
}
int isop(string term){
  if(term[0]=='(' || term[0]==')'){
        return 3;
    }
    else if(term[0]=='*' || term[0]=='+' || term[0]=='-' || term[0]=='/'){
        return 2;
    }
    return 1;
}
bool exppair(char exp ,char top){
     if(top == '(' && exp == ')') //if the top of stack is opening and the expression is respective closing brackets.
          return true;
     if(top == '{' && exp == '}')
          return true;
     if(top == '[' && exp == ']')
          return true;
     return false;//default.
};
bool isvalidparenthesis(string &inStr){
     stack<char> s;
     for(int i = 0; i < inStr.length(); i++){
          if(inStr[i] == '(' || inStr[i] == '[' || inStr[i] == '{')
               s.push(inStr[i]);
          else if(inStr[i] == ')' || inStr[i] == ']' || inStr[i] == '}'){
               if (s.empty() || !exppair(inStr[i], s.top())){ return false; }
               else{s.pop();}
          }
     }
     if(s.empty()){
          for (int i=0; i<inStr.length(); i++){//this makes it compatible with the infix to postfix method. brute force, but works.
               if(inStr[i] == '{')
                    inStr[i] = '(';
               if(inStr[i] == '}')
                    inStr[i] = ')';
               if(inStr[i] == '[')
                    inStr[i] = '(';
               if(inStr[i] == ']')
                    inStr[i] = ')';
          }
          return true;
     }
     return false; //default if the program screws up
}
//!somehow its broken. it worked before.
string infixtopostfix(string input){
     stack<string> s; 
     string result = "" ; //will store the final postfix result.
     string term="";
     //*process on it as a string.
     if(!input.empty() && (input.find(" ") == string::npos)){//input is a single number 
          return input;
     }
     while (!input.empty()){//while input is not empty
          term = input.substr(0,input.find(" ")); //store the term;
          if (isop(term) == 1){//current term is operand
               result += term +",";// append the operand onto the result string.
          }
          
          else if (term == "("){//current term is opening brace
               s.push("(");
          }
          else if (term == ")") {//current term is closing brace. pop till you hit "("
               while (s.top() != "(") {
                    result += s.top()+",";
                    s.pop();
               }
               s.pop();//discard the opening brace
          }
          
          else if (isop(term) == 2){//term is an operator
               while (!s.empty() && (prec(s.top()[0]) >= prec(term[0])) && s.top()[0] != ')'){ 
               // found s.top to be higher precedence than current node, and current is not open bracket
                    result += s.top()+",";//add the operator to result
                    s.pop(); //pop the top of the stack
               }
               s.push(term); // current term is higher precedence than s.top, push it.
          }
          if(input.find(" ") == string::npos)
          break;
          input = input.substr(input.find(" ")+1);
     }

     //empty the rest of the stack 
     while (!s.empty()){ // empty out the remaining operators in the stack
          result += s.top(); //append the term on top
          s.pop(); //pop the top term
     }
     return result;
}
//* btw, this method assumes seperators are commas, you may need to change it for using spaces.
double evalpostfix(string input){
     string term = input.substr(0, input.find(","));
	double result = 0;
	stack<double> s;
	while(!input.empty()){
		term = input.substr(0,input.find(",")); //store the term;
		if (isop(term) == 1){//current node is operand
			s.push(std::stod(term));
		}
		else if (isop(term) == 2){//current node is operator
			double op2 = (double) (s.top()); s.pop(); // pop second operand
			double op1 = (double) (s.top()); s.pop();// pop first operand. lifo remember?
			//calculate:
			if(term[0] == '*'){result = ((op1)*(op2));}
			else if(term[0] == '+'){result = (op1+op2);}
			else if(term[0] == '-'){result = ((op1)-(op2));}
			else if(term[0] == '/'){result = ((op1)/(op2));}
			//push result:
			s.push(result);//perform operation and push back on stack
		}
		if(input.find(",") ==string::npos) //stops descent into chaos
			break;
		input = input.substr(input.find(",")+1); //reduce by one term
	}
	result = s.top(); //done correctly, top value is the answer
	s.pop();
	return result; // its result but whatever
}
struct node{
     string equation;
     double priority;
     node *next;
};
class queue{
     private:
          node *head;
          node *tail;
          //int size; //idk why. might need it.
     public:
          queue() { head = tail = nullptr; };//done
          ~queue();//done
          void push(string, double); //done //inserts based on double. lower values up front.
          node* pop(); //done //returns the entire node at the head.
          bool isempty(){ return head == nullptr;}
          void print(ofstream&);//done

};
queue::~queue(){
     node* cu = head;
     while(head != nullptr){
          head = head->next; //move head to next element
          delete cu;//delete current head
          cu = head; //set the new head as current. for next iteration
     }
};
void queue::push(string equation, double priority){
     node* temp; //make a new node
     temp->equation = equation;
     temp->priority = priority;
     temp->next = nullptr;
     node *cu = head;
     //todo case where queue is empty
     //todo case where there is one node in the queue. idk if the while loop will implode
     while (priority >= cu->priority){ //smaller priority first. so if prio < cu->prio we found the right place.
          head = head ->next; //move head away from the battle
          cu->next = nullptr;//break the link to head.
          tail->next = cu;//move cu to last in queue. 
          tail = tail->next; //otherwise tail'd get buried in the middle somewhere.
          cu = head; //iterator condition.
     }
     temp->next = head; //place it fron of the queue
     head = temp; //move head one back.
     
     cu = head;//redundancy.
     while(cu->priority <= cu->next->priority){//sorted correctly, cu > next means cu is the last node in the array and next the first.
          head = head ->next; //move head away from the battle
          cu->next = nullptr;//break the link to head.
          tail->next = cu;//move cu to last in queue. 
          tail = tail->next; //otherwise tail'd get buried in the middle somewhere.
          cu = head; //iterator condition.
     }//now the queue is ordered.
};
void queue::print(ofstream &out){
     node *cu = head;
     while(cu->priority <= cu->next->priority){//go through the entire queue.
          out << cu->equation ;
          if(cu->next !=nullptr){ out << endl; }//pesky newline.
          //rest of the reordering business:
          head = head ->next; //move head away from the battle
          cu->next = nullptr;//break the link to head.
          tail->next = cu;//move cu to last in queue. 
          tail = tail->next; //otherwise tail'd get buried in the middle somewhere.
          cu = head; //iterator condition.
     }//now the queue is printed and back to where it was.
};
node* queue::pop(){
     node *temp = head;
     if(head != nullptr)//as long as its not empty.
          head = head->next;
     return temp;
}
int main(int argc, char* argv[]){
     ArgumentManager am(argc,argv);
     //ifstream input(am.get("input"));
     //ifstream command(am.get("command"));
     //ofstream out(am.get("output"));
     ifstream input("input1.txt");
     ifstream command("command1.txt");
     ofstream output("output1.txt");
     string inStr;
     queue q;
     while(getline(input, inStr)){
          inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
          inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
          inStr.erase(remove(inStr.begin(), inStr.end(), ' '), inStr.end());
          if(inStr.empty())
               continue;
          double priority = 0.0;
          cout << inStr << endl;
          if(!isvalidparenthesis(inStr)){
               cout << "continuing on. equation not valid"<<endl;
               continue;
          }
          cout << inStr<<endl;
          inStr = infixtopostfix(inStr);
          cout << "postfix form: " << inStr <<endl;
     }

     return 0;
}