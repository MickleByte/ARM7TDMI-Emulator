#pragma once
#include "ALU.h"
#include "controlUnit.h"


//Public:
	//Control Function
	 int ALU::Control(std::string Opcode,  int Operand1,  int Operand2, ControlUnit* cu)
	{
		int ReturnVal = 0;
		if (Opcode == "ADD")
		{
			ValidateADD(cu, Operand1, Operand2);
			ReturnVal = ADD(Operand1, Operand2);
		}
		else if (Opcode == "SUB")
		{
			ValidateSUB(cu, Operand1, Operand2);
			ReturnVal = SUB(Operand1, Operand2);
		}
		else if (Opcode == "MUL")
		{
			ValidateMUL(cu, Operand1, Operand2);
			ReturnVal = MUL(Operand1, Operand2);
		}
		else if (Opcode == "AND")
		{
			ReturnVal = AND(Operand1, Operand2);
		}
		else if (Opcode == "EOR")
		{
			ReturnVal = EOR(Operand1, Operand2);
		}
		else if (Opcode == "ORR")
		{
			ReturnVal = ORR(Operand1, Operand2);
		}
		else if (Opcode == "CMP")
		{
			CMP(Operand1, Operand2, cu);
		}
		return ReturnVal;
	}


//Private:
	//Core ALU Functions
	 int ALU::ADD( int Operand1,  int Operand2)
	{
		 int result = 0;
		result = Operand1 + Operand2;
		return result;
	}

	 int ALU::SUB( int Operand1,  int Operand2)
	{
		 int result = 0;
		result = Operand1 - Operand2;
		return result;
	}

	 int ALU::MUL( int Operand1,  int Operand2)
	{
		 int result = 0;
		result = Operand1 * Operand2;
		return result;
	}

	 int ALU::AND( int Operand1,  int Operand2)
	{
		std::bitset<32> bOperand1 = ConvertToBinary(Operand1); // convert int operands to binary operands
		std::bitset<32> bOperand2 = ConvertToBinary(Operand2);

		std::bitset<32> bResult = bOperand1 &= bOperand2; // perform AND operation & store in bResult

		 int iResult = ( int)(bResult.to_ulong()); // convert bResult to int iResult
		return iResult;
	}

	 int ALU::EOR( int Operand1,  int Operand2)
	{
		std::bitset<32> bOperand1 = ConvertToBinary(Operand1); // convert int operands to binary operands
		std::bitset<32> bOperand2 = ConvertToBinary(Operand2);

		std::bitset<32> bResult = bOperand1 ^= bOperand2; // perform XOR operation & store in bResult

		 int iResult = ( int)(bResult.to_ulong()); // convert bResult to int iResult
		return iResult;
	}

	 int ALU::ORR( int Operand1,  int Operand2)
	{
		std::bitset<32> bOperand1 = ConvertToBinary(Operand1); // convert int operands to binary operands
		std::bitset<32> bOperand2 = ConvertToBinary(Operand2);

		std::bitset<32> bResult = bOperand1 |= bOperand2; // perform OR operation & store in BinResult

		 int iResult = ( int)(bResult.to_ulong()); // convert BinResult to int iResult
		return iResult;
	}

	void ALU::CMP( int Operand1,  int Operand2, ControlUnit* cu)
	{
		 int iCPSR = cu->getRegister(31); // get int val of CPSR (R31)
		std::bitset<32> bCPSR = ConvertToBinary(iCPSR); // converts int val of CPSR to binary value

		ValidateSUB(cu, Operand1, Operand2);
		int difference = SUB(Operand1, Operand2); // gets difference of operand 1 or 2
		if (difference == 0) //if difference is 0, operands are equal
		{
			bCPSR.set(30, true); // change 30th bit (zero flag) of CPSR to True
		}
		else // operands are not equal
		{
			bCPSR.set(30, false); // change 30th bit (zero flag) of CPSR to False
		}

		iCPSR = ( int)(bCPSR.to_ulong()); // convert back to int
		cu->setRegister(31, iCPSR); // set CPSR to new val
	}

	//Other Functions needed for Core ALU Functions (e.g. Abstraction of validation & binary conversions)

	std::bitset<32> ALU::ConvertToBinary( int val)
	{
		std::bitset<32> BinVal = val; // convert int val to 32 bit binary num
		return BinVal;
	}

	void ALU::ValidateADD(ControlUnit* cu,  int Operand1,  int Operand2)
	{
		 int iCPSR = cu->getRegister(31); // get int val of CPSR (R31)
		std::bitset<32> bCPSR = ConvertToBinary(iCPSR); // converts int val of CPSR to binary value




		 if (((Operand2 > 0) && (Operand1 > (INT_MAX - Operand2))) || ((Operand2 < 0) && (Operand1 < (INT_MIN - Operand2))))
		 {
			 bCPSR.set(28, true); // set overflow flag to TRUE
		 }


		iCPSR = (int)(bCPSR.to_ulong()); // convert back to int
		cu->setRegister(31, iCPSR); // set CPSR to new value
	}

	void ALU::ValidateSUB(ControlUnit* cu, int Operand1, int Operand2)
	{
		int iCPSR = cu->getRegister(31); // get int val of CPSR (R31)
		std::bitset<32> bCPSR = ConvertToBinary(iCPSR); // converts int val of CPSR to binary value

		 int MinIntSize =  -2147483647;


		 if ((Operand2 > 0 && Operand1 < INT_MIN + Operand2) || (Operand2 < 0 && Operand1 > INT_MAX + Operand2)) {
			 bCPSR.set(28, true); // set overflow flag to TRUE
		 }


		iCPSR = ( int)(bCPSR.to_ulong()); // convert back to int
		cu->setRegister(31, iCPSR); // set CPSR to new value
	}

	void ALU::ValidateMUL(ControlUnit* cu,  int Operand1,  int Operand2)
	{
		int iCPSR = cu->getRegister(31); // get int val of CPSR (R31)
		std::bitset<32> bCPSR = ConvertToBinary(iCPSR); // converts int val of CPSR to binary value

		long long int LLIoperand1 = (long long int)Operand1;
		long long int LLIoperand2 = (long long int)Operand2;

		long long int Temp = LLIoperand1 * LLIoperand2; // check calculation and store in Temp

		if ((Temp > INT_MAX) || (Temp < INT_MIN)) // if temp is too large or small
		{
			bCPSR.set(28, true); // set overflow flag to TRUE
		}

		iCPSR = ( int)(bCPSR.to_ulong()); // convert back to int
		cu->setRegister(31, iCPSR); // set CPSR to new value
	}
