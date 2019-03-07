#pragma once
#include "ALU.h"
#include "controlUnit.h"
#include "memory.h"

int main(){
  ControlUnit* cu = new ControlUnit();
  ALU alu;

  for(int i = 0; i < 3; i++){
    std::cout << "Intruction " << i << std::endl;
    cu->Decode(cu->FetchNext());
  }

  return 0;
}
