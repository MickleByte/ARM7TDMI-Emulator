#pragma once
#include "ALU.h"
#include "ControlUnit.h"
#include "memory.h"
#include <fstream>

int main(int arg){
  ControlUnit* cu = new ControlUnit();
  // ALU alu;
  // std::cout << alu.Control("ADD", 1, 2, new Register) << std::endl;

  bool debug = true;
  if(arg == 1){
    debug = false;
  }

  std::ofstream registerLog;
  std::ofstream memoryLog;
  std::ofstream assemblyLog;

  registerLog.open("registerLog.log", std::ofstream::out | std::ofstream::trunc);
  memoryLog.open("memoryLog.log", std::ofstream::out | std::ofstream::trunc);
  assemblyLog.open("assemblyLog.log", std::ofstream::out | std::ofstream::trunc);

  for(int i = 0; i < cu->programLength; i++){
    assemblyLog << cu->FetchNext(true) << std::endl;
  }

  cu->setRegister(15, 0);

  for(int i = 0; cu->getRegister(15) < cu->programLength; i++){
    std::string nextInstruction = cu->FetchNext(debug);
    cu->Decode(nextInstruction, debug);
    for(int ii = 0; ii < 1024; ii++){
      memoryLog << cu->getMemory(ii) << " ";
    }
    for(int ii = 0; ii < 37; ii++){
      registerLog << cu->getRegister(ii) << " ";
    }
    memoryLog << std::endl;
    registerLog << std::endl;
  }

  return 0;
}
