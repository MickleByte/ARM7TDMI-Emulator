#pragma once
#include <iostream>
#include <bitset>
#include <limits.h>
#include "Register.h"

class ALU {
public:
	int Control(std::string Opcode, int Operand1, int Operand2, Register* CPSR); // Decodes opcode and conducts ALU functions (e.g. ADD, MUL etc.)
private:

	//Core ALU Functions
	int ADD(int Operand1, int Operand2); // adds 2 operands, returns result
	int SUB(int Operand1, int Operand2); // subtracts 2 operands, returns result
	int MUL(int Operand1, int Operand2); // multiplies 2 operands, returns result
	int AND(int Operand1, int Operand2); // bitwise AND comparison, returns result
	int EOR(int Operand1, int Operand2); // bitwise XOR comparison, returns result
	int ORR(int Operand1, int Operand2); // bitwise OR comparison, returns result
	int CMP(int Operand1, int Operand2, Register* CPSR); // Compare equal to, updates zero flag of program status register (True if equal, False if not equal)


	//Other Functions needed for Core ALU Functions (e.g. Abstraction of validation & binary conversions)
	std::bitset<32> ConvertToBinary(int val);
	void ValidateADD(Register* CPSR, int Operand1, int Operand2);
	void ValidateSUB(Register* CPSR, int Operand1, int Operand2);
	void ValidateMUL(Register* CPSR, int Operand1, int Operand2);

};
