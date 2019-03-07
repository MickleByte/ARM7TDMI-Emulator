#include "pch.h"
#include "ALU.h"
#include "controlUnit.h"



std::bitset<32> ConvertToBinary(int val)
{
	std::bitset<32> BinVal = val; // convert int val to 32 bit binary num
	return BinVal;
}

bool TestADD(Register* CPSR, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;
	int TestResult;

	//Test ADD Function

	//Adding 2 positive ints
	if (!(TestALU.Control("ADD", 121, 41, CPSR) == (121 + 41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 positive integers \n");
	}

	//Adding 2 negative ints
	if (!(TestALU.Control("ADD", -121, -41, CPSR) == (-121 + (-41))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 negative integers \n");
	}

	//adding a negative int to a positive int
	if (!(TestALU.Control("ADD", 121, -41, CPSR)) == (121 + (-41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding a negative int to a positive int \n");
	}

	//adding 1 to max value (2^32) to cause overflow
	std::bitset<32> OldbCPSR = ConvertToBinary(CPSR->get());
	TestResult = TestALU.Control("ADD", INT_MAX, 1, CPSR);
	std::bitset<32> NewbCPSR = ConvertToBinary(CPSR->get());

	if (!((TestResult == (INT_MIN)) && (OldbCPSR.test(28) != NewbCPSR.test(28))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow \n");
	}

	CPSR->set(0);

	return ErrorFlag;
}

bool TestSUB(Register* CPSR, ALU TestALU, std::string &ErrorComment)
{


	bool ErrorFlag = false;
	int TestResult;

	//Test ADD Function

	//Subtracting 2 positive ints
	if (!(TestALU.Control("SUB", 121, 41, CPSR) == (121 - 41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when Subtracting 2 positive integers \n");
	}

	//Adding 2 negative ints
	if (!(TestALU.Control("SUB", -121, -41, CPSR) == (-121 - (-41))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when Subtracting 2 negative integers \n");
	}

	//adding a negative int to a positive int
	if (!(TestALU.Control("SUB", 121, -41, CPSR)) == (121 - (-41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when Subtracting a negative int from a positive int \n");
	}

	//adding 1 to max value (2^32) to cause overflow
	std::bitset<32> OldbCPSR = ConvertToBinary(CPSR->get());
	TestResult = TestALU.Control("SUB", INT_MIN, 1, CPSR);
	std::bitset<32> NewbCPSR = ConvertToBinary(CPSR->get());

	if (!((TestResult == (INT_MAX)) && (OldbCPSR.test(28) != NewbCPSR.test(28))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow \n");
	}

	CPSR->set(0);

	return ErrorFlag;


}


bool TestMUL(Register* CPSR, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;
	long long int TestResult;

	//Test ADD Function

	//Adding 2 positive ints
	if (!(TestALU.Control("MUL", 121, 41, CPSR) == (121 * 41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 positive integers \n");
	}

	//Adding 2 negative ints
	if (!(TestALU.Control("MUL", -121, -41, CPSR) == (-121 * (-41))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 negative integers \n");
	}

	//adding a negative int to a positive int
	if (!(TestALU.Control("MUL", 121, -41, CPSR)) == (121 * (-41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding a negative int to a positive int \n");
	}

	//Multiply max value (2^32) by two, to cause overflow
	std::bitset<32> OldbCPSR = ConvertToBinary(CPSR->get());
	TestResult = TestALU.Control("MUL", INT_MAX, 2, CPSR);
	std::bitset<32> NewbCPSR = ConvertToBinary(CPSR->get());

	if (!(OldbCPSR.test(28) != NewbCPSR.test(28)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow test 1 \n");
	}

	CPSR->set(0);

	//Multiply Min value (-2^32) by two, to cause overflow
	OldbCPSR = ConvertToBinary(CPSR->get());
	TestResult = TestALU.Control("MUL", INT_MIN, 2, CPSR);
	NewbCPSR = ConvertToBinary(CPSR->get());

	if (!(OldbCPSR.test(28) != NewbCPSR.test(28)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow test 2\n");
	}

	CPSR->set(0);

	return ErrorFlag;
}


bool TestAND(Register* CPSR, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;

	if (!(TestALU.Control("AND", 1431655765, -1431655766, CPSR) == 0))
	{
		ErrorComment.append("Error in Test 1 \n");
		ErrorFlag = true;
	}

	if (!(TestALU.Control("AND", 100, 100, CPSR) == 100))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 2\n");
	}

	if (!(TestALU.Control("AND", 0, 10045654, CPSR) == 0))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 3\n");
	}

	return ErrorFlag;
}

bool TestEOR(Register* CPSR, ALU TestALU, std::string &ErrorComment)
{

	bool ErrorFlag = false;

	if (!(TestALU.Control("EOR", 1431655765, -1431655766, CPSR) == -1))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 1 \n");
	}

	if (!(TestALU.Control("EOR", INT_MAX, INT_MAX, CPSR) == 0))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test21  \n");
	}

	if (!(TestALU.Control("EOR", 10, 6, CPSR) == 12))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 3  \n");
	}

	return ErrorFlag;
}


bool TestORR(Register* CPSR, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;

	if (!(TestALU.Control("ORR", 1431655765, -1431655766, CPSR) == -1))
	{
		ErrorComment.append("Error in Test 1 \n");
		ErrorFlag = true;
	}

	if (!(TestALU.Control("ORR", 0, 100, CPSR) == 100))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 2\n");
	}



	return ErrorFlag;
}


bool TestCMP(Register* CPSR, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;
	long long int TestResult;

	CPSR->set(0); // set CPSR to 0


	std::bitset<32> OldbCPSR = ConvertToBinary(CPSR->get());
	TestResult = TestALU.Control("CMP", 2, 2, CPSR);
	std::bitset<32> NewbCPSR = ConvertToBinary(CPSR->get());

	if (!(OldbCPSR.test(30) != NewbCPSR.test(30)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with CMP test 1 \n");
	}

	CPSR->set(0);




	OldbCPSR = ConvertToBinary(CPSR->get());
	TestResult = TestALU.Control("CMP", 3, 2, CPSR);
	NewbCPSR = ConvertToBinary(CPSR->get());

	if (!(OldbCPSR.test(30) == NewbCPSR.test(30)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with test 2\n");
	}

	CPSR->set(0);



	return ErrorFlag;
}



void RunALUTests()
{
	bool ErrorFlag = false;
	ALU TestALU;
	Register* CPSR = new Register();;
	std::string ErrorComment;

	if (TestADD(CPSR, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in ADD function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestSUB(CPSR, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in SUB function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestMUL(CPSR, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in MUL function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestAND(CPSR, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in AND function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestORR(CPSR, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in ORR function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestEOR(CPSR, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in EOR function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestCMP(CPSR, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in CMP function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (!ErrorFlag)
	{
		std::cout << "All ALU tests run without error" << std::endl;
	}

}

int Run()
{
	//Perform Tests on ALU
	RunALUTests();



	system("Pause");
	return 0;
}