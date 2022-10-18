#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <algorithm>
#include <stack>
#include <iomanip>
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

string getPostfix(string input) {
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

int evaluatePostfix(string exp) {
string term = exp.substr(0, exp.find(","));
	double result = 0;
	stack<double> s;
	while(!exp.empty()){
		term = exp.substr(0,exp.find(",")); //store the term;
		if (isop(term) == 1){//current node is operand
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
			s.push(result);//perform operation and push back on stack
		}
		if(exp.find(",") ==string::npos) //stops descent into chaos
			break;
		exp = exp.substr(exp.find(",")+1); //reduce by one term
	}
	result = s.top(); //done correctly, top value is the answer
	s.pop();
	return result; // its result but whatever
}

char reverseopr(char opr){
	switch (opr){
		case '*': return '/'; break;
		case '+': return '-'; break;
		case '-': return '+'; break;
		case '/': return '*'; break;
	}
	return ' ';
}

int main(int argc, char *argv[]){
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream out(am.get("output"));
	// ifstream input("input1.txt");
	// ofstream out("output3.txt");
	string inStr; // input string
	while (getline(input, inStr)){
		// Lines 20 & 21: Removing '\n' and '\r' from inStr
		inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
		inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
		string lhs = "";
		char opr = ' ';
		int rhs = 0;
		double x = 0;
		bool front = true;
		cout << inStr << " input"<< endl;
		if(inStr.find("x") >0){front = false;} //set front to false if x index is > 0
		if(!front){//x at back. assign everything
			lhs = inStr.substr(0,inStr.find("x")-3);
			opr = inStr.substr(inStr.find("x")-2,1)[0];
			rhs = stoi(inStr.substr(inStr.find("=")+2));
		}
		else if(front){//x at front. assign everything, revrse opr for the calculations
			lhs = inStr.substr(inStr.find("x")+4,inStr.find("=")-1-inStr.find("x")-4);
			opr = (inStr.substr(inStr.find("x")+2,1)[0]); //reverse the opr.
			rhs = stoi(inStr.substr(inStr.find("=")+2));
		}
		lhs = getPostfix(lhs); //lhs is now in postfix form.
		cout << lhs<<endl;
		double temp = evaluatePostfix(lhs); //lhs is now solved.
		cout << temp<<endl;
		//double check my operations for mathematical vailidity.
		if(front){//calculate (rhs) (opr) (lhs); 
			opr = reverseopr(opr); //reverse the operator
			switch(opr){
				case '*': x = (double)rhs * temp; break;
				case '-': x = (double)rhs - temp; break;
				case '+': x = (double)rhs + temp; break;
				case '/': x = (double)rhs / temp; break;
			}
		}
		if(!front){
			switch(opr){
				case '*': x = (double)rhs / temp; break;
				case '+': x = (double)rhs - temp; break;
				case '-': x = temp - (double)rhs; break;
				case '/': x = temp / (double)rhs; break;
			}
		}
			//calculate (lhs) (opr) (rhs)
		out <<fixed << setprecision(2) << x << endl;
	}

	// exp1.print();
	return 0;
}