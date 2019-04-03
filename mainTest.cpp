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

  registerLog.open("registerLog.log", std::ofstream::out | std::ofstream::app);
  memoryLog.open("memoryLog.log", std::ofstream::out | std::ofstream::app);
  assemblyLog.open("assemblyLog.log", std::ofstream::out | std::ofstream::app);

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
    assemblyLog << nextInstruction << std::endl;
  }

  return 0;
}
