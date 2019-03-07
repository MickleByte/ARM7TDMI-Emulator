#include "pch.h"
#include "ControlUnit.h"
#include <fstream>
#include <iostream>
using namespace std;

void ControlUnit::setRegister(int registerNumber, int data) {
	registerArray[registerNumber].set(data);
};

int ControlUnit::getRegister(int registerNumber) {
	return registerArray[registerNumber].get();
};

ControlUnit::ControlUnit() {
	registerArray = new Register[37]();
	for (int i = 0; i < 37; i++) {
		registerArray[i].set(i);
	}
};

ControlUnit::~ControlUnit() {
	delete registerArray;
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

void ControlUnit::Decode(vector<string> ListOfIns) {
	vector<string> SepIns;
	string op;

	for (vector<string>::iterator it = ListOfIns.begin(); it != ListOfIns.end(); it++) {
		for (auto x : *it) {
			if (x == ' ') {
				SepIns.push_back(op);
				op = "";
			}
			else {
				op = op + x;
			}
		}
		SepIns.push_back(op);
		op = "";

		cout << alu.Control(SepIns[0], stoi(SepIns[1]), stoi(SepIns[2]), &registerArray[31]) << endl;


		SepIns.clear();
	}
}