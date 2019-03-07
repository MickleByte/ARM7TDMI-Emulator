#pragma once
#include "memory.h"
#include <iostream>
#include <fstream>
#include <vector>

Memory::Memory(){ //Constructor for Memory object
  std::ifstream file("input.txt"); //Input file is "./input.txt"
  pc.set(0); //Set PC (program counter) to 0
  if(!file){ //If file doesn't exist, throw error
    std::cout << "ERROR: Input file not valid" << std::endl;
  }
  else{
    std::string next;
    int length = 0;
    while(std::getline(file, next)){
      mem.push_back(next); //Push instruction
      length++;
    }
  }
  file.close(); //Close file after use
};

Memory::~Memory(){
  delete &mem; //Prevent memory leak
};

std::string Memory::getNextInstruction(){
  std::string nextInstruction = mem.at(pc.get()); //Next instruction to execute is at position stored at PC
  pc.increment();
  return nextInstruction;
};

void PC::increment(){
  data++; //Default increment by one
};

void PC::increment(int amount){
  data += amount; //Useful for "skip next x instructions if..."
};
