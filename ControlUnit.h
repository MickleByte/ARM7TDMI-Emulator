#pragma once
#include <vector>
#include <string>
#include "Register.h"
#include "Memory.h"
#include "ALU.h"
using namespace std;

class ControlUnit {
private:
	vector<Register*> registerArray;
	ALU* alu;
	Memory mem;

	//0 - 30 are general-purpose registers
	//31 - 36 are status registers
	//Pointers are used so one array can have both general-purpose and specialised registers.
public:
	void setRegister(int register, int data); //Set the value of a register
	int getRegister(int register); //Get the value of a register
	ControlUnit();
	~ControlUnit();
	vector<string> ReadFile(string);
	string FetchNext(bool);
	void Decode(string, bool);
	int programLength;
	std::bitset<32> ConvertToBinary(int val);
	int getValueOfArg(string);
	int getMemory(int location);

	int ValidateInstructionCondition(string PotentialInstruct);
	bool ValidCondition(string condition);
	bool ValidInstruction(string instruction);
	bool checkConditionFlag(std::string condition);
};
