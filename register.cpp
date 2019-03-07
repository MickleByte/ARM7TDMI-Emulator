#pragma once
#include "register.h"

int Register::get(){
  return data;
};

void Register::set(int data){
  this->data = data;
};
