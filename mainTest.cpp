#pragma once
#include "ALU.h"
#include "ControlUnit.h"
#include "memory.h"

int main(){
  ControlUnit* cu = new ControlUnit();
  // ALU alu;
  // std::cout << alu.Control("ADD", 1, 2, new Register) << std::endl;

  for(int i = 0; i < cu->programLength; i++){
    cu->Decode(cu->FetchNext());
  }

  return 0;
}
