#include "ControlUnit.h"
#include <fstream>
#include <iostream>
using namespace std;

void ControlUnit::setRegister(int registerNumber, int data) {
	registerArray[registerNumber]->set(data);
};

int ControlUnit::getRegister(int registerNumber) {
	return registerArray[registerNumber]->get();
};

ControlUnit::ControlUnit() {
	for(int i = 0; i < 37; i++){
		if(i == 15){
			PC* pc = new PC;
			pc->set(0);
			registerArray.push_back(pc);
		}
		else{
			registerArray.push_back(new Register);
		}
	}
	alu = new ALU();
};

ControlUnit::~ControlUnit() {
	for(vector<Register*>::iterator it = registerArray.begin(); it != registerArray.end(); it++){
		delete *it;
	}
	delete alu;
}

vector<string> ControlUnit::ReadFile(string path) {
	string ins;
	ifstream myfile(path);
	vector<string> lines;

	if (myfile.is_open()) {
		while (getline(myfile, ins))
			lines.push_back(ins);
	}
	myfile.close();

	return lines;
}

void ControlUnit::Decode(string ListOfIns) {
	string SepIns[3];
	string op = "";

	int i = 0;
	for (string::iterator it = ListOfIns.begin(); it != ListOfIns.end(); it++) {
		if (*it == ' ') {
			SepIns[i] = op;
			op = "";
			i++;
		}
		else {
			op += *it;
		}
	}
	SepIns[i] = op;

	cout << SepIns[0] << " " << SepIns[1] << " " << SepIns[2] << endl;
	// alu->Control(SepIns[0], stoi(SepIns[1]), stoi(SepIns[2]), registerArray[31]);
	cout << alu->Control(SepIns[0], stoi(SepIns[1]), stoi(SepIns[2]), registerArray[31]) << endl;

}

string ControlUnit::FetchNext(){
	string nextInstruction = mem.getNextInstruction(registerArray[15]->get());
	registerArray[15]->increment();
	return nextInstruction;
}





bool ControlUnit::ValidCondition(string condition) 
{
	//list of all valid conditions for ARM7TDMI (According to technical reference manual)
	vector<string> ValidConditions = {"EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE", "AL"};
	
	//Iterate through valid conditions
	for (int i = 0; i < ValidConditions.size(); i++) 
	{
		if (condition == ValidConditions[i]) // if match found
		{
			return true; // condition is valid, so return true
		}
	}
	return false;
}
bool ControlUnit::ValidInstruction(string instruction) 
{
	//list of all valid ARM Instructions for ARM7TDMI (According to technical reference manual)
	vector<string> ValidInstructions = { "MOV", "SUB", "ADD", "MUL", "CMP", "AND", "EOR", "ORR", "B", "BL", "BX", /* "LDR", "STR", "LDC", "MVN", "MRS", "MSR",  "ADC" , "SBC", "RSB" */};

	//Iterate through valid instructions
	for (int i = 0; i < ValidInstructions.size(); i++)
	{
		if (instruction == ValidInstructions[i]) // if match found
		{
			return true; // instruction is valid, so return true
		}
	}
	return false;
}

void ControlUnit::ValidateInstructionCondition(string CondAndInstr)
{
	string condition = CondAndInstr.substr(CondAndInstr.length() - 2); // last 2 letters
	string Instruction = CondAndInstr.substr(0, CondAndInstr.size() - 2); // all but last 2 letters

	bool ValidCond = ValidCondition(condition); // true if valid condition, false if invalid
	bool ValidInstr = ValidInstruction(Instruction);

	if (ValidCond && ValidInstr)
	{
		// check condition then run instruction if true
	}
	else if (!ValidCond && ValidInstr)
	{
		// run instruction only
	}
	else
	{
		// don't run anything
	}

}

