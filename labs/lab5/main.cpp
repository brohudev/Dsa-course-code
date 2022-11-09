#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;
int main(int argc, char* argv[]){
     ArgumentManager am(argc,argv);
     ifstream input(am.get("input"));
     ofstream out(am.get("output"));
     // ifstream input("input3.txt");
     // ofstream out("output1.txt");
     string word;
     map<string, int> map;
     while(input >> word){
          word.erase(remove(word.begin(), word.end(), '\n'), word.end());
          word.erase(remove(word.begin(), word.end(), '\r'), word.end());
          if (word.size() == 0)
               continue;
          while(ispunct(word[0]) || ispunct(word[word.length()-1]) || isdigit(word[0]) || isdigit(word[word.length()-1])){ //if beginning or end have punctuation or numbers.
               if(ispunct(word[0]) || isdigit(word[0]))
                    word = word.substr(1);
               else
                    word = word.substr(0,word.length()-1);
          }
          transform(word.begin(), word.end(), word.begin(), ::tolower); //lowercase the whole thang.
          cout << word << endl;
          map[word]++;
     }
     //cout all the keys in the map.
     for(auto i : map){
          out << i.first << ": "<< i.second <<endl;
     }
     return 0;
}