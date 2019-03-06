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
  std::vector<std::string> mem; //Memory is a vector of strings
  Register* registers; //Registers as an array of registers
  PC pc;
public:
  Memory();
  ~Memory();
  std::string getNextInstruction();
  bool branchTo(std::string label);
};
