#include "ArgumentManager.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream output(am.get("output"));
    ifstream input("input1.txt");
    ofstream output("output1.txt");
    size_t row;
    size_t col;
    input >> row; // input row
    input >> col; // input column
    vector<vector<char>> matrix; // input matrix
    // reading the matrix from the input
    for (int i = 0; i < row; i++) {
        vector<char> temp;
        for (int j = 0; j < col; j++) {
            char c;
            input >> c;
            temp.push_back(c);
        }
        matrix.push_back(temp);
    }
    //create a queue of matrix move pairs and add the input into queue.
//while
    //dequeue the matrix and check if its solved.
    //if yes, print the moves. btw initialize moves to 0 for solved case.
    //if not, shift the matrix in the four directions, then check if it is solved. if yes, do out << moves and exit,
    //otherwise add it back onto the queue. 1,2,3,4 for up left down and right.     
        //when doing the mvoes do moves += '1' or smth like that.
//* this simplifies main to barely 15 more lines of code.
    return 0;
}
