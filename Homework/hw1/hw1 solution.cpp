#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[]) {
  // *** You need to open files using argumentmanager when submit your assignment ***
  //ArgumentManager am(argc, argv);
  //ifstream input(am.get("input"));
  //ifstream command(am.get("command"));
  //ofstream out(am.get("output"));

  // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
  ifstream input("input1.txt");
  ifstream command("command1.txt");
  ofstream out("output1.txt");

  string in = "";
  string temp = "";
  vector<string> id;
  vector<string> first;
  vector<string> last;
  vector<string> output;

  while(getline(input, in)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    in.erase(remove(in.begin(), in.end(), ' '), in.end());
    if(in.size() == 0)
      continue;
    
    // continue to process the input below
    vector<string> cSet;
    temp = in.substr(in.find("id:")+3);
    while(in.find(';') != string::npos)
      { 
        cSet.push_back(in.substr(0,in.find(';')));
        in = in.substr(in.find(';')+1);
        }

    for(int i=0; i < cSet.size(); i++) {
      string alp = cSet[i].substr(0, 1);
      int index = temp.find(cSet[i].substr(0, 1));
      string numb = cSet[i].substr(cSet[i].find(':')+1);
      cout << alp << " " << numb << endl;
      while(temp.find(alp) != string::npos) {
        int index = temp.find(alp);
        temp.replace(index, 1, numb);   
      }
      
    }

    cout << temp << endl;    

    
    vector<int> hIndex;
    for(int i=0; i<temp.length(); i++) {

      if(temp[i] == '#') {
        hIndex.push_back(i);
        cout << i << endl;
      }
      
    }

    for(int i = 0; i < hIndex.size(); i++) {
      int index = temp.find("#");
      temp.replace(index, 1, to_string(hIndex[i]));
      
    }
    id.push_back(temp);
    
  }

  string cmd = "";

  while(getline(command, cmd)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
    if(cmd.size() == 0)
      continue;
    
    // continue to process the command below
    if(cmd.find("first4:") != string::npos) 
      first.push_back(cmd.substr(7));
    else
      last.push_back(cmd.substr(6));
    }
  for(int i=0; i<first.size(); i++)
    cout << first[i] << endl;

  for(int i=0; i<last.size(); i++)
    cout << last[i] << endl;

  for(int i=0; i<id.size(); i++){
    if(first.size() && last.size()) {
      if(count(first.begin(), first.end(), id[i].substr(0, 4)) && 
        count(last.begin(), last.end(), id[i].substr(id[i].length()-4))) {
        output.push_back(id[i]);
        }
      }
    }
  


    
  }