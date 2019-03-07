#pragma once
#include "memory.h"
#include <iostream>

int main(){
  Memory* mem = new Memory();
  std::cout << mem->getNextInstruction() << std::endl;
  std::cout << "Done" << std::endl;
  delete mem;
  return 0;
}
