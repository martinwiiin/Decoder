#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include <string_view>
//#include "Functions.cpp"

using namespace std;


//removing invalid entrys function
vector<string> inValid(vector<string> main){
  vector<string> temp;
  string inVal = "id";
  for(int i=0;i<main.size();i++){ //looping through each entrys
    string base = main.at(i); //assigning each entry to a string
    size_t found = base.find(inVal); //returns index of id if found
    if(found == string::npos){ //nothing found
      continue; //contiues the loop
    }
    else if(found > 0){ //if something found and does not start at 0
      temp.push_back(base); //puts it into vector
    }
  }
  return temp;//sends back cleaned vector
  }



//replace # with its index function
string change(string in){
  vector<int> temp;
  string hold;

  for(int i=0;i<in.size();i++){
    if(in.at(i)=='#'){
      temp.push_back(i);
    }
  }
  for(int i=temp.size()-1;i>-1;i--){
    hold = to_string(temp.at(i));
    
    in.replace(temp.at(i),1,hold);
  }
  return in;
}

//returns vector after command file used
/*vector<string> compare(vector<string> fin, vector<string> cVec, vector<string> oVec){
  vector<string> temp;
  string idHold;
  string base;
  string cBase; 
  string oBase;
  
  for(int i=0;i<fin.size();i++){ //iterate elements
    base = fin.at(i); //turn element into string
    cBase = cVec.at(i);
    oBase = oVec.at(i);
    string idHold;
    string cHold;
    for(int j=0;j<base.size();j++){
      if(cBase[0] == 'f'){
        cHold = oBase[j];
        idHold = base.substr(0,4);
        if(cHold.compare(idHold) == 0){
          temp.push_back(base);
        }
      }
    }
    
  }

  

  

  return temp;
}*/


int main(int argc, char* argv[]) {
  // *** You need to open files using argumentmanager when submit your assignment ***
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ifstream command(am.get("command"));
  ofstream out(am.get("output"));

  // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
  //ifstream input("input2.txt");
  //ifstream command("command4.txt");
  //ofstream out("output1.txt");


  
  string in = "";
  vector<string> main,charSet,IDs,rVec,cleanID,cVec,firstVec,lastVec,comVec,fPass,lPass,orderedV;
  string inVal = "id";
  //string hash = "#";
  while(getline(input, in)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    in.erase(remove(in.begin(), in.end(), ' '), in.end());
    if(in.size() == 0){
      continue;
    }
    else{
      main.push_back(in);
      //cout << in << endl; //testing what it outputs
    }
    
    // continue to process the input below
    
  }
  
  //getChar(hud,in);

  main = inValid(main);
  
  /*for(int i=0; i<main.size();i++){ //prints out vector elements test
    cout << main[i] << endl;
  }*/

  
  for(int i=0;i<main.size();i++){ //looping through each entrys
    string base = main.at(i);
    string tempChar = "";
    string tempID = "";
    size_t found = base.find(inVal);
    for(int j=0;j<found;j++){ //iterating through string
      tempChar += base.at(j);
    }
    charSet.push_back(tempChar);
    for(int k=found+3;k<base.size();k++){
      tempID += base.at(k);
    }
    IDs.push_back(tempID);
    }
  
  /*for(int i=0; i<charSet.size();i++){ //prints out vector elements test
    cout << "vectorSet - " << charSet[i] << endl;
  }*/
  
  /*for(int i=0; i<IDs.size();i++){ //prints out vector elements test
    cout << IDs[i] << endl;
  }*/

  //the decoding function
  for(int i; i<IDs.size();i++){ //loops through elements
    string cEntry = charSet.at(i);
    string cAdd;
    string done;
    string base = IDs.at(i); //turns vector element into string
    for(int j=0;j<base.size();j++){ //iterates through the string
      char set = base.at(j); //turns each string letter into a character
      if(isalpha(set)){ //this checks the character if its an alphabet
        for(int k=0;k<cEntry.size();k++){
          if(set == cEntry.at(k)){
            for(int l=0;l<cEntry.size(); l++){
              // .find only finds the very first ; and :
              cAdd = cEntry.substr(cEntry.find(set)+2);
              // if using first on case 2 with set being u. this would set cAdd to 931;i:5;k:89;p:7;
              cAdd = cAdd.substr(0, cAdd.find(";")); //creates a substring of cAdd and takes only the numbers
              done += cAdd;
              break;
            }
          } 
        }
      }
      else{ //if its not a letter, adds it to done
        done += set;  
      }  
    }
    //cout << "This is decoded - " << done << endl;
    rVec.push_back(done);
    //cout << "cEntry set - " << cEntry << endl;
    //cout << "This is cTemp - " << cTemp << endl;
  }
  

  //removing hashtags
  for(int i=0;i<rVec.size();i++){
    string in = rVec.at(i);
    string newin;

    newin = change(in);
    cleanID.push_back(newin);
  }
  
  

  /*for(int i=0;i<rVec.size();i++){ //prints out vector elements
    cout << "Replace Vec - " << rVec[i] << endl;
  }*/

  for(int i=0;i<cleanID.size();i++){ //prints out vector elements
    cout << "CleanedID Vec - " << cleanID[i] << endl;
  }
  
  /*fin = change(rVec);

  for(int i=0;i<fin.size();i++){
    cout << "Final vec - " << fin[i] << endl;
  }*/
  



  string cmd = "";

  while(getline(command, cmd)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
    if(cmd.size() == 0){
      continue;
    }
    else{ // continue to process the command below
      cVec.push_back(cmd);
      //cout << cmd << endl;
    }
  }

  for(int i=0; i<cVec.size();i++){
    cout << "Command Vec - " << cVec[i] << endl;
  }
  
  if(cVec.size() == 0){
    for(int i=0;i<cleanID.size();i++){
      out << cleanID.at(i) << endl;
    }  
  }
  
  for(int i=0;i<cVec.size();i++){ //iterate cVec elements
    string base = cVec.at(i); //turns cVec elements into a string
    string fHold;
    string lHold;
    //cout << "string base - " << base << endl;
    for(int j=0;j<base.size();j++){ //iterates through string
      if(base[0] == 'f'){
        fHold = base.substr(base.find(":")+1);
        firstVec.push_back(fHold);
        //cout << "first - " << base.substr(base.find(":")+1) << endl;
        break;
      }
      else if(base[0] == 'l'){
        lHold = base.substr(base.find(":")+1);
        lastVec.push_back(lHold);
        //cout << "last - " << base.substr(base.find(":")+1) << endl;
        break;
      }  
      /*else if(base[0] == string::npos){
        for(int i=0;i<cleanID.size();i++){
          cout << "test - " << cleanID.at(i) << endl;
        }
      }*/
    }
  }

  for(int i=0;i<firstVec.size();i++){
    cout << "firstVec - " << firstVec[i] << endl;
  }

  for(int i=0;i<lastVec.size();i++){
    cout << "lastVec - " << lastVec[i] << endl;
  }

  //check if there was a first command 
  if(firstVec.size() > 0){
    for(int i=0;i<firstVec.size();i++){
      string chopID;
      string command = firstVec.at(i);
      for(int j=0;j<cleanID.size();j++){
        string idHold = cleanID.at(j);
          for(int k=0;k < command.size();k++){
            chopID.push_back(idHold.at(k));
          }
        if(chopID == command){
          fPass.push_back(idHold);
        }
        chopID.clear();
      }
    }
  }

  if(lastVec.size() > 0){
    for(int i=0;i<lastVec.size();i++){
      string chopID;
      string command = lastVec.at(i);
      for(int j=0;j<cleanID.size();j++){
        string idHold = cleanID.at(j);
          for(int k=idHold.size()-command.size();k < idHold.size();k++){
            chopID.push_back(idHold.at(k));
            //cout << "chopID - " << chopID << endl;
          }
        //cout << "idHold - " << chopID << endl;
        //cout << "command - " << command << endl;
        if(chopID == command){
          lPass.push_back(idHold);
          //cout << "idHold - " << idHold << endl;
        }
        chopID.clear();
      }
    }
  }

  if((lPass.size() > 0) && (fPass.size() > 0)){
    for(int i=0;i<lPass.size();i++){
      string lBase = lPass.at(i);
      for(int j=0;j<fPass.size();j++){
        string fBase = fPass.at(j);
        if(fBase == lBase){
          comVec.push_back(fBase);
        }
      }
    }
  }
  else if(fPass.size() > 0){
    for(int i=0;i<fPass.size();i++){
      comVec.push_back(fPass.at(i));
    }
  }
  else if(lPass.size() > 0){
    for(int i=0;i<lPass.size();i++){
      comVec.push_back(lPass.at(i));
    }
  }
  /*else if((lPass.size() == 0) && (fPass.size() == 0)){
    for(int i=0;i<cleanID.size();i++){
      orderedV.push_back(cleanID.at(i));
  }*/
  
  for(int i=0;i<cleanID.size();i++){
    string base = cleanID.at(i);
    for(int j=0;j<comVec.size();j++){
      string cBase = comVec.at(j);
      if(base == cBase){
        orderedV.push_back(base);
      }
    }
  }
  
    
  for(int i=0;i<orderedV.size();i++){
    out << orderedV.at(i) << endl;
  }

  
  
  
  return 0;
}
  
