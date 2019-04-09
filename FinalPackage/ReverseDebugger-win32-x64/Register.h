#pragma once
class Register {
protected:
	int data; //The value of this register
public:
	int get(); //Get the value of this register
	void set(int data); //Set the value of this register
	virtual void increment();
	virtual void increment(int amount);
	Register();
};

class PC : public Register{
public:
  virtual void increment();
  virtual void increment(int amount);
};
