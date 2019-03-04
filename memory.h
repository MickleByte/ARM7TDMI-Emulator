//Memory object definition

//Program counter
//Get next instruction
//Move program counter
//Increment program counter
//Branch to (label)

#include <string>
#include "register.h"

class PC : public Register{
public:
  void increment();
  void increment(int amount);
}

class Memory{
private:
  std::string* mem;
  Register pc;
public:
  std::string getNextInstruction();
  std::string branchTo(std::string label);
}
