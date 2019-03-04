#include "controlUnit.h"
#include "iostream"

int main(){
  ControlUnit* cu = new ControlUnit();
  std::cout << cu->getRegister(0) << std::endl;
  delete cu;
  return 0;
}
