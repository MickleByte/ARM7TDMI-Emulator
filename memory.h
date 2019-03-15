#pragma once
#include <string>
#include "register.h"
#include <vector>

class Memory{
private:
  std::vector<std::string> program; //Program is a vector of strings
  std::vector<int> mem; //Memory is a vector of ints
public:
  Memory();
  ~Memory();
  std::string getNextInstruction(int pc);
  bool branchTo(std::string label);
  int getMemory(int location);
  void setMemory(int location, int value);
};
