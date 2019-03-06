//Memory object definition

//Program counter
//Get next instruction
//Move program counter
//Increment program counter
//Branch to (label)

#pragma once
#include <string>
#include "register.h"
#include <vector>

class PC : public Register{
public:
  void increment();
  void increment(int amount);
};

class Memory{
private:
  std::vector<std::string> mem;
  Register* registers;
  PC pc;
public:
  Memory();
  ~Memory();
  std::string getNextInstruction();
  bool branchTo(std::string label);
};
