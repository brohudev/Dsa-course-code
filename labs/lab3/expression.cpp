#include "expression.h"
#include <string>
#include <iostream>
#include <stack>
using namespace std;

expression::expression(){
    exphead = nullptr;
    answer =0;
};
expression::~expression(){
    node *cu = exphead;
    while (cu != nullptr)
    {
        node *temp = cu;
        cu = cu->next;
        delete temp;
        temp = nullptr;
    }
};

bool expression::assignopr(string input){
    if(input == "+"){return true;}
    if(input == "-"){return true;}
    if(input == "*"){return true;}
    if(input == "/"){return true;}
    if(input == "("){return true;}
    if(input == ")"){return true;}
    return false;
};
int expression::isop(string term){
    if(term[0]=='(' || term[0]==')'){
        return 3;
    }
    else if(term[0]=='*' || term[0]=='+' || term[0]=='-' || term[0]=='/'){
        return 2;
    }
    return 1;
};
int expression::prec(char c){
      if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
};
string expression::getexp(){ return exp; };

string expression::infixtopostfix(string input){ 
     stack<string> s; 
    string result = "" ; //will store the final postfix result.
    string term="";
    //*process on it as a string.
    if(!input.empty() && (input.find(" ") == string::npos)){//input is a single number 
        exp = input;
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
            while (!s.empty() && (prec(s.top()[0]) > prec(term[0])) && s.top()[0] != ')'){ 
            // found s.top to be higher precedence than current node, and current is not open bracket
                result += term+",";//add the operator to result
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
    exp = result;//set this into the exp.
    return result;
};
bool expression::evalpostfix(string exp){
            string term = exp.substr(0, exp.find(","));
        double result = 0;
        stack<double> s;
        while(!exp.empty()){
            term = exp.substr(0,exp.find(",")); //store the term;
            cout << term<<" is the term"<<endl;
            if (isop(term) == 1){//current node is operand
                cout<<"pushing operand"<<term<<endl;
                s.push(stod(term));
            }
            else if (isop(term) == 2){//current node is operator
                //! second * in input 3 is lost. why? intopostfix malfunctioning smh
                double op2 = (double) (s.top()); s.pop(); // pop second operand
                double op1 = (double) (s.top()); s.pop();// pop first operand. lifo remember?
                //calculate:
                if(term[0] == '*'){result = ((op1)*(op2));}
                else if(term[0] == '+'){result = (op1+op2);}
                else if(term[0] == '-'){result = ((op1)-(op2));}
                else if(term[0] == '/'){result = ((op1)/(op2));}
                //push result:
                cout<<"pushing result: "<< result<<endl;
                s.push(result);//perform operation and push back on stack
            }
            if(exp.find(",") ==string::npos) //stops descent into chaos
                break;
            exp = exp.substr(exp.find(",")+1); //reduce by one term
        }
        result = s.top(); //done correctly, top value is the answer
        s.pop();
        cout <<"answer  "<<result<<endl;
        return true; // its result but whatever
};

bool expression::isempty(){ return (exphead == nullptr); }
void expression::print(){ cout << exp <<endl; }