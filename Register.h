#pragma once
class Register {
private:
	int data; //The value of this register
public:
	int get(); //Get the value of this register
	void set(int data); //Set the value of this register
};