#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

//recursive function that will return true if we reach the target number
bool calculate(int** matrix, int r, int c, int target, int count, 
                int rows, int cols, bool** visited);

int main(int argc, char* argv[]) {
    //ArgumentManager am(argc, argv);
    //ifstream inputfile(am.get("input"));
    //ofstream outputfile(am.get("output"));

    ifstream inputfile("input3.txt");
    ofstream outputfile("output3.txt");
    
    int row, column;
    int target;
    int xZero, yZero;

    //file is empty
    if (inputfile.peek() == EOF) {
        outputfile << "Not Possible" << endl;
        inputfile.close();
        outputfile.close();
        return 0;
    }

    //get row and col from input
    inputfile >> row >> column;

    //create 2 matrix, 1 to store the input, 1 to check visited path
    int** matrix = new int*[row]; //matrix
    bool** visited = new bool*[row]; //matrix

    for (int i=0; i<row; i++) { //turn every row cell in both matrices into an array.
        matrix[i]= new int[column];
        visited[i]= new bool[column];
    }

    //store input into a 2d array, and get the position of 0
    for(int i=0; i < row; i++)
        for(int j=0; j < column; j++) {
            inputfile >> matrix[i][j]; 
            visited[i][j] = false; //init all to "not visited"  
            if(matrix[i][j] == 0) { //stores the index of the starting 0
                xZero = i;
                yZero = j;
            }
        }

    //get the target number from the input
    inputfile >> target;

    //call the recursive function
    if(calculate(matrix, xZero, yZero, target, 0, row, column, visited))
    {
        cout << "Possible" << endl;
        outputfile << "Possible" << endl;
    }
    else
    {
        cout << "Not Possible" << endl;
        outputfile << "Not Possible" << endl;
    }

    //Destructor and closing files
    for(int i=0;i<row;i++)
    {
        delete[] matrix[i];
        delete[] visited[i];
    }
    delete[] matrix;
    delete[] visited;
    inputfile.close();
    outputfile.close();

    return 0;
};

bool calculate(int** matrix, int rIndex, int cIndex, int target, int currCount, 
                int maxRows, int maxCols, bool** visited)
{
    //check for out of bounds and already visited path
    if(rIndex < 0 || rIndex >= maxRows || cIndex < 0 || cIndex >= maxCols || visited[rIndex][cIndex])
        return false;
    currCount += matrix[rIndex][cIndex];
    if(currCount == target)
        return true;
    visited[rIndex][cIndex] = true; //set to true for this path taker
    if(calculate(matrix, rIndex-1, cIndex, target, currCount, maxRows, maxCols, visited) || //up
        calculate(matrix, rIndex+1, cIndex, target, currCount, maxRows, maxCols, visited) || //down
        calculate(matrix, rIndex, cIndex-1, target, currCount, maxRows, maxCols, visited) || //left
        calculate(matrix, rIndex, cIndex+1, target, currCount, maxRows, maxCols, visited)) //right
        return true;
    visited[rIndex][cIndex] = false; //reset to false for the next path takers
    return false;
};