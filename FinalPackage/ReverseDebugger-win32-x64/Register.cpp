#include "pch.h"
#include "register.h"
#include <iostream>

Register::Register(){
	data = 0;
}

int Register::get() {
	return data;
};

void Register::set(int data) {
	this->data = data;
};

void Register::increment(){
	std::cout << "ERROR: Can't increment this register" << std::endl;
}

void Register::increment(int amount){
	std::cout << "ERROR: Can't increment this register" << std::endl;
}

void PC::increment(){
  data++; //Default increment by one
};

void PC::increment(int amount){
  data += amount; //Useful for "skip next x instructions if..."
};
