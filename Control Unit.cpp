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
	programLength = mem.getProgramLength();
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
	string SepIns[4];
	string op = "";
	int result;
	SepIns[3] = "none";

	//decode
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

	//execute
	int validationResult = ValidateInstructionCondition(SepIns[0]);
	std::string instruction = SepIns[0];
	std::string condition = "";

	switch(validationResult){
		case 0:
			//both valid
				condition = SepIns[0].substr(SepIns[0].length() - 2); // last 2 letters
				instruction = SepIns[0].substr(0, SepIns[0].size() - 2); // all but last 2 letters
			if(!checkConditionFlag(condition)){
				break;
			}
		case 1:
			//Instruction valid but not condition
			if (instruction == "STR") {
				mem.setMemory(stoi(SepIns[1]), getRegister(stoi(SepIns[2])));
			}
			else if (instruction == "LDR") {
				setRegister(stoi(SepIns[2]), mem.getMemory(stoi(SepIns[1])));
			}
			else if (instruction == "B"){
				mem.branchTo(SepIns[1], registerArray[15]);
			}
			else {
				cout << instruction << " " << SepIns[1] << " " << SepIns[2] << endl;
				// alu->Control(SepIns[0], stoi(SepIns[1]), stoi(SepIns[2]), registerArray[31]);
				result = alu->Control(instruction, stoi(SepIns[1]), stoi(SepIns[2]), registerArray[31]);
				cout << result << endl;
			}
			if(SepIns[3] != "none"){
				setRegister(stoi(SepIns[3]), result);
				cout << "Stored in r" << SepIns[3] << endl;
			}
		break;

		case 2:
			//Neither valid

		break;
	}
}

std::bitset<32> ControlUnit::ConvertToBinary(int val)
{
	std::bitset<32> BinVal = val; // convert int val to 32 bit binary num
	return BinVal;
}

bool ControlUnit::checkConditionFlag(std::string condition){
	int iCPSR = registerArray[15]->get(); // get int val of CPSR (R31)
	std::bitset<32> bCPSR = ConvertToBinary(iCPSR); // converts int val of CPSR to binary value

	//31 - N - Negative
	//30 - Z - Zero
	//29 - C - Carry
	//28 - V - Overflow

	if("NE"){ //Not Equal
		if(bCPSR[30] == 0) return true;
		else return false;
	}
	else if("EQ"){ //Equal
		if(bCPSR[30] == 1) return true;
		else return false;
	}
	else if("CS"){ //Carry set
		if(bCPSR[29] == 1) return true;
		else return false;
	}
	else if("CC"){ //Carry unset
		if(bCPSR[29] == 0) return true;
		else return false;
	}
	else if("MI"){ //Minus/negative
		if(bCPSR[31] == 1) return true;
		else return false;
	}
	else if("PL"){ //Positive/zero
		if(bCPSR[31] == 0) return true;
		else return false;
	}
	else if("VS"){ //Overflow set
		if(bCPSR[28] == 1) return true;
		else return false;
	}
	else if("VC"){ //Overflow unset
		if(bCPSR[28] == 0) return true;
		else return false;
	}
	else if("HI"){ //Unsigned higher
		if(bCPSR[29] == 1 && bCPSR[30] == 0) return true;
		else return false;
	}
	else if("LS"){ //Unsigned lower or equal
		if(bCPSR[30] == 1 && bCPSR[29] == 0) return true;
		else return false;
	}
	else if("GE"){ //Signed greater than or equal
		if(bCPSR[31] == bCPSR[28]) return true;
		else return false;
	}
	else if("LT"){ //Signed less than
		if(bCPSR[31] != bCPSR[28]) return true;
		else return false;
	}
	else if("GT"){ //Signed greater than
		if(bCPSR[30] == 0 && (bCPSR[31] == bCPSR[28])) return true;
		else return false;
	}
	else if("LE"){ //Signed less than or equal
		if(bCPSR[30] == 1 && (bCPSR[31] != bCPSR[28])) return true;
		else return false;
	}
	else if("AL"){ //Unconditional
		return true;
	}
	else{
		return false;
	}
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
	vector<string> ValidInstructions = { "MOV", "SUB", "ADD", "MUL", "CMP", "AND", "EOR", "ORR", "B", "BL", "BX", "LDR", "STR",/*  "LDC", "MVN", "MRS", "MSR",  "ADC" , "SBC", "RSB" */};

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

int ControlUnit::ValidateInstructionCondition(string CondAndInstr)
{
	string condition = CondAndInstr.substr(CondAndInstr.length() - 2); // last 2 letters
	string Instruction = CondAndInstr.substr(0, CondAndInstr.size() - 2); // all but last 2 letters

	bool ValidCond = ValidCondition(condition); // true if valid condition, false if invalid
	if(!ValidCond){
		Instruction = CondAndInstr;
	}
	bool ValidInstr = ValidInstruction(Instruction);

	if (ValidCond && ValidInstr)
	{
		// check condition then run instruction if true
		return 0;
	}
	else if (!ValidCond && ValidInstr)
	{
		// run instruction only
		return 1;
	}
	else
	{
		// don't run anything
		return 2;
	}

}
