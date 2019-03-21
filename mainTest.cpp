#pragma once
#include "ALU.h"
#include "controlUnit.h"
#include "memory.h"

int main(){
  ControlUnit* cu = new ControlUnit();
  // ALU alu;
  // std::cout << alu.Control("ADD", 1, 2, new Register) << std::endl;

  for(int i = 0; i < 3; i++){
    cu->Decode(cu->FetchNext());
  }

  return 0;
}
