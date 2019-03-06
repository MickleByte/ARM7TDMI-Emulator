#pragma once
#include "memory.h"
#include <iostream>
#include <fstream>
#include <vector>

Memory::Memory(){
  std::ifstream file("input.txt");
  pc.set(0);
  if(!file){
    std::cout << "ERROR: Input file not valid" << std::endl;
  }
  else{
    std::string next;
    int length = 0;
    while(std::getline(file, next)){
      mem.push_back(next);
      length++;
    }
    file.close();
    for(int i = 0; i < length; i++){
      std::cout << mem.at(i) << std::endl;
    }
  }
};

Memory::~Memory(){
  delete &mem;
};

std::string Memory::getNextInstruction(){
  std::string nextInstruction = mem.at(pc.get());
  pc.increment();
  return nextInstruction;
};

void PC::increment(){
  data++;
};

void PC::increment(int amount){
  data += amount;
};
