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
    while(std::getline(file, next)){
      program.push_back(next); //Push instruction
      programLength++;
    }
  }
  file.close(); //Close file after use

  mem.reserve(1024);
};

int Memory::getProgramLength(){
  return programLength;
}

Memory::~Memory(){
  delete &mem; //Prevent memory leak
  delete &program;
};

std::string Memory::getNextInstruction(int pc, bool debug){
  if(debug) std::cout << "Getting instruction at " << pc << std::endl;
  std::string nextInstruction = program.at(pc); //Next instruction to execute is at position stored at PC
  return nextInstruction;
};

int Memory::getMemory(int location) {
  return mem[location];
};

void Memory::setMemory(int location, int value) {
  mem[location] = value;
};

bool Memory::branchTo(std::string label, Register* pc, bool debug){
  if(debug) std::cout << "Searching for label: " << label << std::endl;
  int index = 0;
  for(auto it = program.begin(); it != program.end(); it++){
    if(*it == label){
      pc->set(index+1);
      if(debug) std::cout << "Label found at " << index << std::endl;
      return true;
    }
    index++;
  }
  return false;
};
