#include <vector>
#include <string>
#include "Register.h"
using namespace std;

class ControlUnit {
private:
	Register* registerArray;

	//0 - 30 are general-purpose registers
	//31 - 36 are status registers
	//Pointers are used so one array can have both general-purpose and specialised registers.
public:
	void setRegister(int register, int data); //Set the value of a register
	int getRegister(int register); //Get the value of a register
	ControlUnit();
	~ControlUnit();
	vector<string> ReadFile(string);
	void Decode(vector<string>);
};
