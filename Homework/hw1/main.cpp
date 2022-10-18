#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[]) {
  // *** You need to open files using argumentmanager when submit your assignment ***
  ArgumentManager am(argc, argv);
   ifstream input(am.get("input"));
   ifstream command(am.get("command"));
   ofstream out(am.get("output"));

  // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
  // ifstream input("input3.txt");
  // ifstream command("command3.txt");
  // ofstream out("output3.txt");

  string in = "";   //captures the input into a string
  string temp = "";
  vector<string> id;  //vector that stores the id of the input
  vector<string> first;   //the vector that store shte numbers of first four type of commands.
  vector<string> last;    //the vectore stores last 4 type commands
  vector<string> output;   //vector that has the output strings filtered through the command file.

  while(getline(input, in)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    in.erase(remove(in.begin(), in.end(), ' '), in.end());
    if(in.size() == 0)
      continue;
    
   
    // continue to process the input below
    vector<string> cSet;//store the id and the replacement letter
    temp = (in.substr(in.find("id:")+3)); //stores the id
    while(in.find(';') != string::npos){//while you keep findng ;seperated things, upend the text in between to cSet
      cSet.push_back(in.substr(0, in.find(';')));
      in = in.substr(in.find(';')+1);//delete everything before the current thing.
    }

    for(int i=0; i<cSet.size(); i++){//go through cSet
       string alp = cSet[i].substr(0, 1);//alp is the character in every cell
      int index = temp.find(cSet[i].substr(0, 1)); //index of alp in the id(stored into temp)
      string numb = cSet[i].substr(cSet[i].find(':')+1); //the number crrspnding with the alp
      
      while(temp.find(alp) != string::npos) {//as long as alp is in the id:
        int index = temp.find(alp);//find alp's index
        temp.replace(index, 1, numb);//replace it with the num
      }
      
    }
    vector<int> hIndex; //stores the indexes of all hashes.
    for(int i=0; i<temp.length(); i++){//for every char in temp
      if(temp[i] == '#'){//if char is #
        hIndex.push_back(i); //uppend the index val
      }
    }

    for(int i=0; i<hIndex.size();i++){//iterate for all #s
      int index = temp.find('#');
      temp.replace(index, 1, to_string(hIndex[i]));//replace # with the i'th num in hIndex.
    }
    id.push_back(temp); //store the sorted id.
    
  }
  for(int i=0;i<id.size();i++)
    cout<<i<<" is "<<id[i]<<endl;

  string cmd = "";

  while(getline(command, cmd)) {
    // Clean up blank spaces, \n and \r, and skip blank lines    
    cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());    
    // store each into their respective vectors.
    if(cmd.empty()){continue;}
    else if (cmd.at(0) == 'f')
      {first.push_back(cmd.substr(7));}
    else if(cmd.at(0) == 'l')
     {last.push_back(cmd.substr(6));}
    
  }

  for (int i = 0; i < first.size(); i++)
  {
    cout <<"first[i]: "<< first[i] << endl;
  }
  for (int i = 0; i < last.size(); i++)
  {
    cout <<"last[i]"<< last[i] << endl;
  }
 
 bool isfirstcmd = !first.empty();
 bool islastcmd = !last.empty();
 
  for(int i=0; i<id.size(); i++){
    cout<<"iteration "<<i<<endl;

    if(isfirstcmd && islastcmd) {//case 1, both cmds present
     if(count(first.begin(), first.end(), id[i].substr(0, 4)) && count(last.begin(), last.end(), id[i].substr(id[i].length()-4))) {
        output.push_back(id[i]);
        cout<<"a both match found. "<<id[i]<<" is getting pushed"<<endl;
        }
      }

    else if(!isfirstcmd && islastcmd){
      if(count(last.begin(), last.end(), id[i].substr(id[i].length()-4))) {
        output.push_back(id[i]);
        cout << "only last math found. "<<id[i]<<" is getting pushed"<<endl;
        
      }
    }
    
    if(isfirstcmd && !islastcmd){
        if(count(first.begin(), first.end(), id[i].substr(0, 4))){
          output.push_back(id[i]);
          cout<<"only first match found "<<id[i]<<" is getting pushed"<<endl;
        }
    
    }
    else if(first.empty() && last.empty()){  
        output.push_back(id[i]);    
        cout<< "no cmd found. pushing id"<<id[i]<<" to output"<< endl;
        
    }


  }
  for (int i = 0; i < output.size(); i++)
  {
    cout << "the output is: " << output[i]<< endl;
    out << output[i] << endl;
    
    
  }
  
}