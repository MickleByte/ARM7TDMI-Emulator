#pragma once
#include <string>
#include "register.h"
#include <vector>

class Memory{
private:
  std::vector<std::string> program; //Program is a vector of strings
  std::vector<int> mem; //Memory is a vector of ints
  int programLength;
public:
  Memory();
  ~Memory();
  int getProgramLength();
  std::string getNextInstruction(int pc);
  bool branchTo(std::string label, PC pc);
  int getMemory(int location);
  void setMemory(int location, int value);
};
