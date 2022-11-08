#include "ArgumentManager.h"
#include "Queue.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

bool isMatch(char left, char right) {
    if      ((left == '{') && (right != '}')) {return false;}

    else if ((left == '[') && (right != ']')) {return false;}

    else if ((left == '(') && (right != ')')) {return false;}
    
    return true;
}

bool isPairType(char c) {
    if ((c == '{') || (c == '}') || (c == '[') || (c == ']') || (c == '(') || (c == ')')) {
        return true;
    }
    return false;
}

bool isRedundantPair(string expression, int left, int right) {
    if (left == right - 1) {
        return true;
    }

    if ((left == 0) || (right == expression.size() - 1)) {
        if (isPairType(expression.at(left + 1)) && isPairType(expression.at(right - 1))) {
            if (isMatch(expression.at(left + 1), expression.at(right - 1))) {
                return true;
            }
        }
        return false;
    }

    if (isPairType(expression.at(left - 1)) && isPairType(expression.at(right + 1))) {
        if (isMatch(expression.at(left - 1), expression.at(right + 1))) {
            return true;
        }
    }
    return false;
}

string removePair(string expression, int left, int right) {
    string removed;
    for (int i = 0; i < left; i++) {
        removed += expression.at(i);
    }

    for (int i = left + 1; i < right; i++) {
        removed += expression.at(i);
    }

    for (int i = right + 1; i < expression.size(); i++) {
        removed += expression.at(i);
    }
    return removed;
}

bool isValid(string expression) {
    if (expression.size() == 0) {
        return false;
    }
    int lastFrontBrace       = expression.rfind('{');
    int lastFrontBracket     = expression.rfind('[');
    int lastFrontParenthesis = expression.rfind('(');

    int lastEndBrace;
    int lastEndBracket;
    int lastEndParenthesis;
    if (lastFrontBrace != string::npos) {
        lastEndBrace         = expression.substr(lastFrontBrace      , expression.size()).find('}');
        if (lastEndBrace != string::npos) {
            lastEndBrace += lastFrontBrace;
        }
    }
    else {
        lastEndBrace = expression.rfind('}');
    }

    if (lastFrontBracket != string::npos) {
        lastEndBracket       = expression.substr(lastFrontBracket    , expression.size()).find(']');
        if (lastEndBracket != string::npos) {
            lastEndBracket += lastFrontBracket;
        }
    }
    else {
        lastEndBracket = expression.rfind(']');
    }

    if (lastFrontParenthesis != string::npos) {
        lastEndParenthesis   = expression.substr(lastFrontParenthesis, expression.size()).find(')');
        if (lastEndParenthesis != string::npos) {
            lastEndParenthesis += lastFrontParenthesis;
        }
    }
    else {
        lastEndParenthesis = expression.rfind(')');
    }

    if ((lastFrontBrace == string::npos) && (lastEndBrace == string::npos) && (lastFrontBracket == string::npos) && (lastEndBracket == string::npos) && (lastFrontParenthesis == string::npos) && (lastEndParenthesis == string::npos)) {
        return true;
    }

    if ((((lastFrontBrace != string::npos) && (lastEndBrace == string::npos)) || ((lastFrontBrace == string::npos) && (lastEndBrace != string::npos))) || (((lastFrontBracket != string::npos) && (lastEndBracket == string::npos)) || ((lastFrontBracket == string::npos) && (lastEndBracket != string::npos))) || (((lastFrontParenthesis != string::npos) && (lastEndParenthesis == string::npos)) || ((lastFrontParenthesis == string::npos) && (lastEndParenthesis != string::npos)))) {
        return false;
    }

    if ((lastFrontBrace != string::npos) && (lastEndBrace != string::npos)) {
        if (isRedundantPair(expression, lastFrontBrace, lastEndBrace)) {
            return false;
        }
        else {
            expression = removePair(expression, lastFrontBrace, lastEndBrace);
            return isValid(expression);
        }
    }

    if ((lastFrontBracket != string::npos) && (lastEndBracket != string::npos)) {
        if (isRedundantPair(expression, lastFrontBracket, lastEndBracket)) {
            return false;
        }
        else {
            expression = removePair(expression, lastFrontBracket, lastEndBracket);
            return isValid(expression);
        }
    }

    if ((lastFrontParenthesis != string::npos) && (lastEndParenthesis != string::npos)) {
        if (isRedundantPair(expression, lastFrontParenthesis, lastEndParenthesis)) {
            return false;
        }
        else {
            expression = removePair(expression, lastFrontParenthesis, lastEndParenthesis);
            return isValid(expression);
        }
    }
    return true;
}
// Above are functions to determine an expression's validity according to parenthesis/brackets/braces
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p(char op)
{
    if (op == '}') 
    {
        return -6;
    }

    else if (op == '{') 
    {
        return -5;
    }

    if (op == ']') 
    {
        return -4;
    }

    else if (op == '[') 
    {
        return -3;
    }

    if (op == ')') 
    {
        return -2;
    }

    else if (op == '(') 
    {
        return -1;
    }

    else if ((op == '+') || (op == '-'))
    {
        return 1;
    }

    else if ((op == '*') || (op == '/'))
    {
        return 2;
    }
    return 0;
}

bool isOperator(char c) {
    if ((c == '+') || (c == '-') || (c == '*') || (c == '/')) {
        return true;
    }
    else {
        return false;
    }
}

void toPostfix(stack<char>& ops, string& numStr, char data)
{
    if (isdigit(data)) {
        numStr += data;
        return;
    }

    if (ops.empty()) {
        ops.push(data);
        return;
    }

    char topOp = ops.top();
    if ((p(data) > p(topOp)) || (p(data) == -1) || (p(data) == -3) || (p(data) == -5)) {
        ops.push(data);
        return;
    }
    else {
        while ((!ops.empty()) && (p(data) <= p(topOp))) {
            if (p(data) == -2) {
                bool leftPar = false;
                while (!leftPar) {
                    if (ops.top() == '(') {
                        leftPar = true;
                        ops.pop();
                        continue;
                    }
                    numStr += ops.top();
                    ops.pop();
                    if (!ops.empty()) {
                        topOp = ops.top();
                    }
                }
                return;
            }

            if (p(data) == -4) {
                bool leftBracket = false;
                while (!leftBracket) {
                    if (ops.top() == '[') {
                        leftBracket = true;
                        ops.pop();
                        continue;
                    }
                    numStr += ops.top();
                    ops.pop();
                    if (!ops.empty()) {
                        topOp = ops.top();
                    }
                }
                return;
            }

            if (p(data) == -6) {
                bool leftBrace = false;
                while (!leftBrace) {
                    if (ops.top() == '{') {
                        leftBrace = true;
                        ops.pop();
                        continue;
                    }
                    numStr += ops.top();
                    ops.pop();
                    if (!ops.empty()) {
                        topOp = ops.top();
                    }
                }
                return;
            }
            numStr += ops.top();
            ops.pop();
            if (!ops.empty()) {
                topOp = ops.top();
            }
        }
        ops.push(data);
    }
    return;
}

double operation(double lower, double higher, char op){
    if(op == '+') {
        return lower + higher;
    }
    else if(op == '-') {
        return lower - higher;
    }
    else if(op == '*') {
        return lower * higher;
    }
    else if(op == '/') {
        return lower / higher;
    }
    return 0;
}

double expressionValue(string expression) {
    return 0;
}

// Above are operations relating to infix -> postfix conversion / the evaluation of a postfix expression
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Next two functions are for a type of priority queue

void newQ(int minIndx, Queue& editedQ, Queue& originalQ){
    int sizeOgQ = originalQ.getSize();
    for(int o = 0; o < sizeOgQ; o++){
        if(o != minIndx){
        originalQ.enqueue(originalQ.getFrontExpression(), originalQ.getFrontValue());
        originalQ.dequeue();           
        }
        if(o == minIndx){
            editedQ.enqueue(originalQ.getFrontExpression(), originalQ.getFrontValue());
            originalQ.dequeue();
        }
    }
}

int getMinIndx(Queue& originalQ){
    int minIndx = 0;
    int c = 0;
    double min = originalQ.getFrontValue();
    validExpression * cu = originalQ.getFront();

    while( cu != nullptr){
        if (cu->value < min){
            min = cu->value;
            minIndx = c;
        }
        cu = cu->next;
        c++;
    }
    return minIndx;
}

int main (int argc, char * argv[]) {
    ArgumentManager am(argc, argv);
    ofstream output (am.get("output"));
    ifstream input (am.get("input"));
    string expression = "";
    Queue finalQueue;
    Queue expQueue;
    double value;
   while (getline(input, expression))
    {
        expression.erase(remove(expression.begin(), expression.end(), '\n'), expression.end());
        expression.erase(remove(expression.begin(), expression.end(), '\r'), expression.end());
        expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
        if (!isValid(expression)) {
            continue;
        }
        stack<char> opStack;
        string postFix = "";

        for (int i = 0; i < expression.size(); i++) {
            toPostfix(opStack, postFix, expression.at(i));
        }
        while (!opStack.empty()) {
            postFix += opStack.top();
            opStack.pop();
        }

        stack<double> numStack;
        for (int i = 0; i < postFix.size(); i++) {
            char cu = postFix.at(i);
            if (isdigit(cu)) {
                numStack.push(stof(postFix.substr(i, 1)));
            }
            else if (isOperator(cu)) {
                double highest = numStack.top();
                numStack.pop();
                double lower = numStack.top();
                numStack.pop();
                numStack.push(operation(lower, highest, cu));
            }
        }
        double expValue = numStack.top();
        //cout << "Expression: " << expression << endl << "Postfix: " << postFix << endl << "Value: " << expValue << endl << endl;
        value = expressionValue(expression);
        expQueue.enqueue(expression, expValue);
    }    
    //expQueue.print(output);
    int Qsize = expQueue.getSize();
    for(int o = 0; o < Qsize; o++){
        int minLocation = getMinIndx(expQueue);
        newQ(minLocation, finalQueue, expQueue);
    }
    cout << endl << endl;
    finalQueue.print(output);
   return 0;
}