// #include <stdlib>

#include <iostream>
#include <fstream>
#include <sstream>
// #include <cstream>
#include <vector>
#include<stdlib.h>

#include "ctype.h"
#include "filereader.h"
using namespace std;

std::vector<mob_description> read_file(std::string file_name){
  vector<mob_description> r ;
  mob_description *mob;
  //$HOME/.rlg327/
  ifstream filename (file_name.c_str());
  //cout<<"hello"<<endl;
  while(!filename.eof()){
  mob= new mob_description;
  string str;
  filename >> str;
  std::cout << str <<endl;
  if(str == "RLG327"){
    str +=str;
    filename >> str;
    std::cout << str <<endl;
    if(str == "MONSTER" ){
      str +=str;
      filename >> str;
      std::cout << str <<endl;
      if(str == "DESCRIPTION"){
        str +=str;
        filename >> str ;
        std::cout << str <<endl;
        if(str != "1"){
          return std::vector<mob_description>();
        }
      }
      else{
        return std::vector<mob_description>();
    }
  }else{
      return vector<mob_description>();
  }
}
  if(str == "NAME" ){
    getline(filename, str);
    mob->name = str;
    continue;
  }
  if(str == "BEGIN"){
    filename >> str;

    continue;
  }
  if(str == "SYMB"){
    getline(filename,str);
    mob->symbol = str[0];
    continue;
  }
  // parse the color and the dice: speed, Dam, Hp
  if(str == "COLOR"){
    getline(filename,str);
    // for(uint i = 0; i < str.length();i++){

    // }
// cannot get

    continue;
  }
  if(str == "DESC"){
      getline(filename,str);
      while(str != "."){
      mob->descrption += str;
      getline(filename,str);
    }
      continue;
  }
  if(str == "SPEED"){
    getline(filename,str);
    std::vector<string> v;
    uint32_t  plus = str.find("+");
    uint32_t dee = str.find("d");
    int b =atoi(str.substr(0, plus).c_str());
    int c =atoi(str.substr(plus+1, dee).c_str());
    int s =atoi( str.substr(dee+1, str.size()).c_str());
    mob->speed =  dice(s,b,c);
    // mob.speed = str;
    continue;
    }
    if(str == "DAM"){
      getline(filename ,str);
      // std::vector<string> v;
      uint32_t  plus = str.find("+");
      uint32_t dee = str.find("d");
      int b =atoi( str.substr(0, plus).c_str());
      int c =atoi( str.substr(plus+1, dee).c_str());
      int s=atoi( str.substr(dee+1, str.size()).c_str());
      mob->attack = dice(s,b,c);
      continue;
    }
    if(str == "HP"){
      getline(filename,str);
      std::vector<string> v;
      uint32_t  plus = str.find("+");
      uint32_t dee = str.find("d");
      int b =atoi( str.substr(0, plus).c_str());
      int c =atoi( str.substr(plus+1, dee).c_str());
      int s =atoi( str.substr(dee+1, str.size()).c_str());
      mob->hp = dice(s,b,c);
      continue;
    }
    if(str == "ABIL"){
      getline(filename,str);
      // cannot get
      continue;
    }
    if(str == "END"){
      //  r.push_back(r,*mob);
      getline(filename,str);
      mob = new mob_description;


    }
    std::cout << str <<endl;
}
  return r;
}
