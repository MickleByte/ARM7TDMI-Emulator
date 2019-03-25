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
	string SepIns[4] = {"", "", "", ""};
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

	int Args[3];

	for(int i = 1; i < SepIns.length; i++){
		if(SepIns[i] != ""){
			Args[i-1] = getValueOfArg(SepIns[i]);
		}
	}

	//execute
	int validationResult = ValidateInstructionCondition(SepIns[0]);
	std::string instruction = SepIns[0];
	std::string condition = "";
	bool conditionResult = false;

	switch(validationResult){
		case 0:
			//both valid
			condition = SepIns[0].substr(SepIns[0].length() - 2); // last 2 letters
			instruction = SepIns[0].substr(0, SepIns[0].size() - 2); // all but last 2 letters
			conditionResult = checkConditionFlag(condition);
			std::cout << "Checking condition: " << condition << std::endl;
			if(!conditionResult){
				std::cout << "Condition returned false" << std::endl;
				break;
			}
			std::cout << "Condition returned true" << std::endl;
		case 1:
			//Instruction valid but not condition
			if (instruction == "STR") {
				mem.setMemory(Args[0], getRegister(Args[1]));
			}
			else if (instruction == "LDR") {
				setRegister(Args[1], mem.getMemory(Args[1]));
			}
			else if (instruction == "B"){
				mem.branchTo(Args[0], registerArray[15]);
			}
			else {
				cout << instruction << " " << Args[0] << " " << Args[1] << endl;
				// alu->Control(SepIns[0], stoi(SepIns[1]), stoi(SepIns[2]), registerArray[31]);
				result = alu->Control(instruction, Args[0], Args[1], registerArray[31]);
				if(instruction == "CMP"){
					registerArray[31]->set(result);
				}
				cout << result << endl;
			}
			if(SepIns[3] != "none"){
				setRegister(Args[2], result);
				cout << "Stored in r" << Args[2] << endl;
			}
		break;

		case 2:
			//Neither valid

		break;
	}
}

int getValueOfArg(std::string argument){
	if(argument[0] == 'R'){ //Lokesh

	}
	else if(argument[0] == '#'){ //Hayden

	}
	else{ //Dinkie
		std::cout << "ERROR: Must include either R or # prefix" << std::endl;
		return 0;
	}
}

std::bitset<32> ControlUnit::ConvertToBinary(int val)
{
	std::bitset<32> BinVal = val; // convert int val to 32 bit binary num
	return BinVal;
}

bool ControlUnit::checkConditionFlag(std::string condition){
	int iCPSR = registerArray[31]->get(); // get int val of CPSR (R31)
	std::bitset<32> bCPSR = ConvertToBinary(iCPSR); // converts int val of CPSR to binary value

	//31 - N - Negative
	//30 - Z - Zero
	//29 - C - Carry
	//28 - V - Overflow

	if(condition == "NE"){ //Not Equal
		if(!bCPSR[30]) return true;
	}
	else if(condition == "EQ"){ //Equal
		if(bCPSR[30]) return true;
	}
	else if(condition == "CS"){ //Carry set
		if(bCPSR[29]) return true;
	}
	else if(condition == "CC"){ //Carry unset
		if(!bCPSR[29]) return true;
	}
	else if(condition == "MI"){ //Minus/negative
		if(bCPSR[31]) return true;
	}
	else if(condition == "PL"){ //Positive/zero
		if(!bCPSR[31]) return true;
	}
	else if(condition == "VS"){ //Overflow set
		if(bCPSR[28]) return true;
	}
	else if(condition == "VC"){ //Overflow unset
		if(!bCPSR[28]) return true;
	}
	else if(condition == "HI"){ //Unsigned higher
		if(bCPSR[29] && !bCPSR[30]) return true;
	}
	else if(condition == "LS"){ //Unsigned lower or equal
		if(bCPSR[30] && !bCPSR[29]) return true;
	}
	else if(condition == "GE"){ //Signed greater than or equal
		if(bCPSR[31] == bCPSR[28]) return true;
	}
	else if(condition == "LT"){ //Signed less than
		if(bCPSR[31] != bCPSR[28]) return true;
	}
	else if(condition == "GT"){ //Signed greater than
		if(!bCPSR[30] && (bCPSR[31] == bCPSR[28])) return true;
	}
	else if(condition == "LE"){ //Signed less than or equal
		if(bCPSR[30] && (bCPSR[31] != bCPSR[28])) return true;
	}
	else if(condition == "AL"){ //Unconditional
		return true;
	}
	return false;
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
