#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[]){
     ArgumentManager am(argc,argv);
     //ifstream input(am.get("input"));
     //ifstream command(am.get("command"));
     //ofstream out(am.get("output"));
     ifstream input("input1.txt");
     ifstream command("command1.txt");
     ofstream out("output1.txt");
     string inStr;
     
     while(getline(input, inStr)){
          
     }
     return 0;
}