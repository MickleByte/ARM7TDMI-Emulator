#pragma once
#include "ALU.h"
#include "ControlUnit.h"
#include "memory.h"

int main(int arg){
  ControlUnit* cu = new ControlUnit();
  // ALU alu;
  // std::cout << alu.Control("ADD", 1, 2, new Register) << std::endl;

  bool debug = true;
  if(arg == 1){
    debug = false;
  }

  for(int i = 0; cu->getRegister(15) < cu->programLength; i++){
    cu->Decode(cu->FetchNext(debug), debug);
  }

  return 0;
}
