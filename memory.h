#pragma once
#include <string>
#include "register.h"
#include <vector>

class Memory{
private:
  std::vector<std::string> mem; //Memory is a vector of strings
public:
  Memory();
  ~Memory();
  std::string getNextInstruction(int pc);
  bool branchTo(std::string label);
};
