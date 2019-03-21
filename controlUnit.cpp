#pragma once
#include "controlUnit.h"

void ControlUnit::setRegister(int registerNumber, int data){
  registerArray[registerNumber].set(data);
};

int ControlUnit::getRegister(int registerNumber){
  return registerArray[registerNumber].get();
};

ControlUnit::ControlUnit(){
  registerArray = new Register[37]();
  for(int i = 0; i < 37; i++){
    registerArray[i].set(i);
  }
};

ControlUnit::~ControlUnit(){
  delete registerArray;
}
