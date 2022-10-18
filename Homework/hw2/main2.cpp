/*It is possible that this code might contain a typo. It is
unlikely but make sure to check your code to ensure it works*/
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node{
  string username;
  int id;
  char grade;
  int score;
  node *next;
};

class linkedList{
  private:
    node *head;
    int size;
  public:
    linkedList(){
      head = nullptr; size = 0;
    }
    int getsize(){ return size;}
    int getid(int pos){
      node *cu = head;
      for (int i = 0; i < pos; i++){ cu = cu->next; }
      return cu->id;
    }
    //todo sort
    void swap(node* cu, node* prev) {
      node *temp = new node;
      temp->id = cu->id;
      temp->username = cu->username;
      temp->score = cu->score;
      temp->grade = cu->grade;
      //move prev to cu
      cu->id = prev->id;
      cu->username = prev->username;
      cu->score = prev->score;
      cu->grade = prev->grade;
      //move cu to prev by proxy of temp
      prev->id = temp->id;
      prev->username = temp->username;
      prev->score = temp->score;
      prev->grade = temp->grade;

    }
    void sortid() {
      node *cu = new node;
      node *prev = new node;
      int swapped = 1;
      cout <<"sorting by id"<<endl;
      while(swapped) {
        swapped = 0;
        cu = head->next;
        prev = head;
        while(cu != nullptr) {
          if(cu->id < prev->id) {
            swap(cu , prev);
            swapped = 1;
          }
          prev = cu;
          cu = cu->next;
        }
      }
    }
    void sortname() {
      node *cu = new node;
      node *prev = new node;
      int swapped = 1;
      cout <<"sorting by name"<<endl;
      while(swapped) {
        swapped = 0;
        cu = head->next;
        prev = head;
        while(cu != nullptr) {
          if((cu->username).compare(prev->username) < 0) {
            swap(cu , prev);
            swapped = 1;
          }
          prev = cu;
          cu = cu->next;
        }
      }
    }
    void sortscore() {
      node *cu = new node;
      node *prev = new node;
      int swapped = 1;
      cout <<"sorting by score"<<endl;
      while(swapped) {
        swapped = 0;
        cu = head->next;
        prev = head;
        while(cu != nullptr) {
          if(cu->score > prev->score) {
            swap(cu , prev);
            swapped = 1;
          }
          prev = cu;
          cu = cu->next;
        }
      }
    }
    void sortgrade() {
      node *cu = new node;
      node *prev = new node;
      int swapped = 1;
      cout <<"sorting by grade"<<endl;
      while(swapped) {
        swapped = 0;
        cu = head->next;
        prev = head;
        while(cu != nullptr) {
          if((cu->grade)<(prev->grade)) {
            swap(cu , prev);
            swapped = 1;
          }
          prev = cu;
          cu = cu->next;
        }
      }
    }
    //todo find
    int findname(string _username){
      node *current = head;
      int index = 0;
      while(current != nullptr){
        if(current->username == _username){
          return index;
        }
        index++;
        current = current->next;
      }
      return -1;
    }
    int findid(int id){
      node *current = head;
      int index = 0;
      while(current != nullptr){
        if(current->id == id){
          return index;
        }
        index++;
        current = current->next;
      }
      return -1;
    }    
    int findscore(int score){
      node *current = head;
      int index = 0;
      while(current != nullptr){
        if(current->score == score){
          return index;
        }
        index++;
        current = current->next;
      }
      return -1;
    }
    int findgrade(char grade){
      node *current = head;
      int index = 0;
      while(current != nullptr){
        if(current->grade == grade){
          return index;
        }
        index++;
        current = current->next;
      }
      return -1;
    }
    //todo print
    void print(ofstream &outputFile){
      node *current = head;
      do{
        outputFile <<"[id:"<< current->id << ";username:" << current->username << ";score:"<<current->score<<";grade:"<<current->grade<<"]";
        if(current->next != nullptr){ outputFile << endl; }
        current = current->next;
        
      }while(current != nullptr);
    }
    void print(){
      node *cu = head;
      cout << "printing"<<endl;
      while (cu != nullptr){
        cout << cu->username << " "<<cu->id<<" "<< cu->score<<" "<<cu->grade<<endl;
        cu= cu->next;
      }
      
    }
    //todo add
    void addatpos(int id, string usrnme, int score, char grade, int pos){
      node *temp= new node();
      temp->id = id;
      temp->username = usrnme;
      temp->score = score;
      temp->grade = grade;
      temp->next = nullptr;

      node *cu = head;
      node *prev = nullptr;

      if(pos >size){ cout << "pos invalid"<<endl;return; }//also does a null list check.
      else if(pos == size){ addatend(id, usrnme, score, grade);} //add at the end of the list
      else{//this is somewhere in the middle of the lsit
        for (int i = 0; i < pos; i++){ prev = cu; cu = cu->next; }
        prev->next = temp;
        temp-> next = cu; 
      }
      size++;
    };
    void addatend(int id, string usrnme, int score, char grade){
      node *temp = new node;
      temp->id= id;
      temp->username = usrnme;
      temp->score = score;
      temp->grade = grade;
      temp->next = nullptr;
      
      if(head == nullptr){ head = temp; size =1; }
      else{
        node *cu = head;
        while(cu->next != nullptr){ cu = cu->next; }
        cu->next = temp;
      }
      size++;
    }
    void addatbeg(int id, string username, int score, char grade){
      node *temp = new node;
      temp->id = id;
      temp->username = username;
      temp->score = score;
      temp->grade = grade;
      temp->next = nullptr;
      if(head == nullptr){ head = temp;}
      else{
        temp->next = head;
        head = temp;
      }
      size++;
    }
    //todo delete
    void remove(int index){
      node *cu = head;
      node *prev = nullptr;
      if(index == -1){ cout<<"can't find a match to remove"<<endl; return; }
      else if(index == 0){
        delete cu, prev; head = nullptr;cout<<"removed the head"<<endl;
      }
      else{//more than one node
          for (int i = 1;i<=index;i++){
              prev = cu; //move the previous node up by one
              cu = cu->next; //move onto the next node
          }
          prev ->next = (cu->next);
          cout<<"deleting"<<cu->id <<cu->username<<cu->score<<cu->grade<<endl;
          delete cu;
          cu = nullptr;
      }
      size--;
    }
    bool isvalid(int idIndex, int userIndex, int scoreIndex, int gradeIndex){
    if(idIndex == -1 || userIndex == -1 || scoreIndex == -1 || gradeIndex == -1){ return false; }
    //Check to see if attributes are in order by doing something like:
    if(idIndex > userIndex || userIndex > scoreIndex || scoreIndex > gradeIndex){ return false; }
    return true;
    }
    //todo update method
    void update(int id, string username, int score, char grade, int pos){
      node *cu = head;
      for (int i = 0; i < pos; i++)//better when you know the pos to travel to
      { cu = cu->next; }
      cu->id = id;
      cu->username = username;
      cu->score = score;
      cu->grade = grade;

    }
};

int main(int argc, char *argv[]){

  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ifstream command(am.get("command"));
  ofstream out(am.get("output"));
  // ifstream input("input3.txt");
  // ifstream command("command3.txt");
  // ofstream out("output3.txt");
  linkedList list;
  string inStr; //input string
  int idIndex, userIndex,ct =1, scoreIndex, gradeIndex = 0;
  string id =""; string username =""; string score =""; string grade =""; int index;
  
  while(getline(input, inStr)){
    cout << inStr<<endl;
    //Lines 20 & 21: Removing '\n' and '\r' from inStr
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
    //Getting the first index of each substring that is found from inStr
    idIndex = inStr.find("id:");  
    userIndex = inStr.find("username:");
    scoreIndex = inStr.find("score:");
    gradeIndex = inStr.find("grade:");
    //If there is a missing attribute, continue
    if(!list.isvalid(idIndex,userIndex,scoreIndex,gradeIndex)){continue;}
    //Continue to parse inStr
    string id ="";
    string username ="";
    string score ="";
    string grade ="";
    id = inStr.substr(idIndex+3, 4);
    username = inStr.substr(userIndex+9, (scoreIndex-1)-(userIndex+9));
    score = inStr.substr(scoreIndex+6, (gradeIndex-1)-(scoreIndex+6));
    grade = inStr.substr(gradeIndex+6, 1);
    //Input into linked list
    cout << list.findid(stoi(id))<<" name pos: "<<list.findname(username)<<endl;
    if(list.findid(stoi(id)) > (-1)){
        list.update(stoi(id), username, stoi(score), grade[0], list.findid(stoi(id)));
      }
    else if(list.findname(username) > -1){//found a username match
      if(list.getid(list.findname(username)) == stoi(id)){//found an id match
        list.update(stoi(id), username, stoi(score), grade[0], list.findid(stoi(id)));
      }
      else{cout << "found usrnme but not id"<<endl; ct++; continue;}
    }
    else{list.addatend(stoi(id), username, stoi(score), grade[0]);}
  }
  while(getline(command, inStr)){
    cout << inStr<<endl;
    //Lines 20 & 21: Removing '\n' and '\r' from inStr
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
    //Getting the first index of each substring that is found from inStr

    if(inStr[0]=='A'){
      
      //!duplicates still are acting up.
      //bucket the credentials
      idIndex = inStr.find("id:");  
      userIndex = inStr.find("username:");
      scoreIndex = inStr.find("score:");
      gradeIndex = inStr.find("grade:");
      int position = inStr.find("(")+1;
      if(!list.isvalid(idIndex,userIndex,scoreIndex,gradeIndex)){cout << "cred invalid"<<endl;continue;}
      //populate all the vars
      id = inStr.substr(idIndex+3, 4);
      username = inStr.substr(userIndex+9, (scoreIndex-1)-(userIndex+9));
      score = inStr.substr(scoreIndex+6, (gradeIndex-1)-(scoreIndex+6));
      grade = inStr.substr(gradeIndex+6, 1);
      index = stoi(inStr.substr(position, (inStr.find(")")-position)));
      //Input into linked list
      if(list.findid(stoi(id)) > (-1)){//found id match
        list.update(stoi(id), username, stoi(score), grade[0], list.findid(stoi(id)));
        ct++; continue;
      }
      else if(list.findname(username) > -1){//found a username match
        if(list.getid(list.findname(username)) == stoi(id)){//found an id match
          list.update(stoi(id), username, stoi(score), grade[0], list.findid(stoi(id)));
        }
        else{cout << "found usrnme but not id"<<endl; ct++; continue;}
      }
      cout << list.findid(stoi(id))<<" name pos: "<<list.findname(username)<<endl;
      if(index == 0){ cout << "adding at beginning"<<endl;list.addatbeg(stoi(id), username, stoi(score), grade[0]); ct++; continue; }
      else if(index == list.getsize()){ cout << "adding at end"<<endl; list.addatend(stoi(id), username, stoi(score), grade[0]); ct++; continue;}
      else{ cout << "adding at pos "<<endl;list.addatpos(stoi(id), username, stoi(score), grade[0], index); ct++; continue;}
    }
    if(inStr[0]=='R'){
      inStr = inStr.substr(inStr.find("(")+1,(inStr.find(")")-(inStr.find("(")+1)));
      if (inStr[0] == 'i'){
        inStr = inStr.substr(3);
        while(list.findid(stoi(inStr)) > -1){
          list.remove(list.findid(stoi(inStr)));
        }
        ct++; continue;
      }
      if (inStr[0] == 'u'){
        inStr = inStr.substr(9);
        while(list.findname(inStr) > -1){
          list.remove(list.findname(inStr));
        }
        ct++; continue;
      }
      if (inStr[0] == 's'){
        inStr = inStr.substr(6);
        while(list.findscore(stoi(inStr)) > -1){
          list.remove(list.findscore(stoi(inStr)));
        }
        ct++; continue;
      }
      if (inStr[0] == 'g'){
        inStr = inStr.substr(6);
        while(list.findgrade(inStr[0]) > -1){
          list.remove(list.findgrade(inStr[0]));
        }
        ct++; continue;
      }
    }
    if(inStr[0]=='S'){
      inStr = inStr.substr(inStr.find("(")+1,(inStr.find(")")-(inStr.find("(")+1)));
      if(inStr[0] =='i'){ list.sortid(); }
      if(inStr[0] =='u'){ list.sortname(); }
      if(inStr[0] =='s'){ list.sortscore(); }
      if(inStr[0] =='g'){ list.sortgrade(); }
      ct++; continue;
    }
    ct++;
  }
  list.print(out);
  return 0;
}