#pragma once
#include "memory.h"
#include <iostream>
#include <fstream>
#include <vector>

Memory::Memory(){ //Constructor for Memory object
  std::ifstream file("input.txt"); //Input file is "./input.txt"
  std::cout << "Read file" << std::endl;
  if(!file){ //If file doesn't exist, throw error
    std::cout << "ERROR: Input file not valid" << std::endl;
  }
  else{
    std::string next;
    int length = 0;
    while(std::getline(file, next)){
      program.push_back(next); //Push instruction
      length++;
    }
  }
  file.close(); //Close file after use

  mem.reserve(1024);
};

Memory::~Memory(){
  delete &mem; //Prevent memory leak
};

std::string Memory::getNextInstruction(int pc){
  std::cout << "Getting instruction at " << pc << std::endl;
  std::string nextInstruction = program.at(pc); //Next instruction to execute is at position stored at PC
  return nextInstruction;
};

int Memory::getMemory(int location) {
  return mem[location];
};

void Memory::setMemory(int location, int value) {
  mem[location] = value;
};
