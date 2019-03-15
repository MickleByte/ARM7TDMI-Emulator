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

	if (SepIns[0] == "STR") {
		setMemory(SepIns[1], getRegister(SepIns[2]));
	}
	else if (SepIns[0] == "LDR") {
		setRegister(SepIns[2]), getMemory(SepIns[1]));
	}
	else {
		cout << SepIns[0] << " " << SepIns[1] << " " << SepIns[2] << endl;
		// alu->Control(SepIns[0], stoi(SepIns[1]), stoi(SepIns[2]), registerArray[31]);
		cout << alu->Control(SepIns[0], stoi(SepIns[1]), stoi(SepIns[2]), registerArray[31]) << endl;
	}
}

string ControlUnit::FetchNext(){
	string nextInstruction = mem.getNextInstruction(registerArray[15]->get());
	registerArray[15]->increment();
	return nextInstruction;
}
