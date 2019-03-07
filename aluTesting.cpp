#include "ALU.h"
#include "controlUnit.h"



std::bitset<32> ConvertToBinary(int val)
{
	std::bitset<32> BinVal = val; // convert int val to 32 bit binary num
	return BinVal;
}

bool TestADD(ControlUnit* TestCu, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;
	int TestResult;

	//Test ADD Function

	//Adding 2 positive ints
	if (!(TestALU.Control("ADD", 121, 41, TestCu) == (121 + 41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 positive integers \n");
	}

	//Adding 2 negative ints
	if (!(TestALU.Control("ADD", -121, -41, TestCu) == (-121 + (-41))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 negative integers \n");
	}

	//adding a negative int to a positive int
	if (!(TestALU.Control("ADD", 121, -41, TestCu)) == (121 + (-41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding a negative int to a positive int \n");
	}

	//adding 1 to max value (2^32) to cause overflow
	std::bitset<32> OldbCPSR = ConvertToBinary(TestCu->getRegister(31));
	TestResult = TestALU.Control("ADD", INT_MAX, 1, TestCu);
	std::bitset<32> NewbCPSR = ConvertToBinary(TestCu->getRegister(31));

	if (!((TestResult == (INT_MIN)) && (OldbCPSR.test(28) != NewbCPSR.test(28))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow \n");
	}

	TestCu->setRegister(31, 0);

	return ErrorFlag;
}

bool TestSUB(ControlUnit* TestCu, ALU TestALU, std::string &ErrorComment)
{


	bool ErrorFlag = false;
	int TestResult;

	//Test ADD Function

	//Subtracting 2 positive ints
	if (!(TestALU.Control("SUB", 121, 41, TestCu) == (121 - 41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when Subtracting 2 positive integers \n");
	}

	//Adding 2 negative ints
	if (!(TestALU.Control("SUB", -121, -41, TestCu) == (-121 - (-41))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when Subtracting 2 negative integers \n");
	}

	//adding a negative int to a positive int
	if (!(TestALU.Control("SUB", 121, -41, TestCu)) == (121 - (-41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when Subtracting a negative int from a positive int \n");
	}

	//adding 1 to max value (2^32) to cause overflow
	std::bitset<32> OldbCPSR = ConvertToBinary(TestCu->getRegister(31));
	TestResult = TestALU.Control("SUB", INT_MIN, 1, TestCu);
	std::bitset<32> NewbCPSR = ConvertToBinary(TestCu->getRegister(31));

	if (!((TestResult == (INT_MAX)) && (OldbCPSR.test(28) != NewbCPSR.test(28))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow \n");
	}

	TestCu->setRegister(31, 0);

	return ErrorFlag;


}


bool TestMUL(ControlUnit* TestCu, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;
	long long int TestResult;

	//Test ADD Function

	//Adding 2 positive ints
	if (!(TestALU.Control("MUL", 121, 41, TestCu) == (121 * 41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 positive integers \n");
	}

	//Adding 2 negative ints
	if (!(TestALU.Control("MUL", -121, -41, TestCu) == (-121 * (-41))))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding 2 negative integers \n");
	}

	//adding a negative int to a positive int
	if (!(TestALU.Control("MUL", 121, -41, TestCu)) == (121 * (-41)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error when adding a negative int to a positive int \n");
	}

	//Multiply max value (2^32) by two, to cause overflow
	std::bitset<32> OldbCPSR = ConvertToBinary(TestCu->getRegister(31));
	TestResult = TestALU.Control("MUL", INT_MAX, 2, TestCu);
	std::bitset<32> NewbCPSR = ConvertToBinary(TestCu->getRegister(31));

	if (!(OldbCPSR.test(28) != NewbCPSR.test(28)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow test 1 \n");
	}

	TestCu->setRegister(31, 0);

	//Multiply Min value (-2^32) by two, to cause overflow
	OldbCPSR = ConvertToBinary(TestCu->getRegister(31));
	TestResult = TestALU.Control("MUL", INT_MIN, 2, TestCu);
	NewbCPSR = ConvertToBinary(TestCu->getRegister(31));

	if (!(OldbCPSR.test(28) != NewbCPSR.test(28)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with overflow test 2\n");
	}

	TestCu->setRegister(31, 0);

	return ErrorFlag;
}


bool TestAND(ControlUnit* TestCu, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;

	if (!(TestALU.Control("AND", 1431655765, -1431655766, TestCu) == 0))
	{
		ErrorComment.append("Error in Test 1 \n");
		ErrorFlag = true;
	}

	if (!(TestALU.Control("AND", 100, 100, TestCu) == 100))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 2\n");
	}

	if (!(TestALU.Control("AND", 0, 10045654, TestCu) == 0))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 3\n");
	}

	return ErrorFlag;
}

bool TestEOR(ControlUnit* TestCu, ALU TestALU, std::string &ErrorComment)
{

	bool ErrorFlag = false;

	if (!(TestALU.Control("EOR", 1431655765, -1431655766, TestCu) == -1))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 1 \n");
	}

	if (!(TestALU.Control("EOR", INT_MAX, INT_MAX, TestCu) == 0))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test21  \n");
	}

	if (!(TestALU.Control("EOR", 10, 6, TestCu) == 12))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 3  \n");
	}

	return ErrorFlag;
}


bool TestORR(ControlUnit* TestCu, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;

	if (!(TestALU.Control("ORR", 1431655765, -1431655766, TestCu) == -1))
	{
		ErrorComment.append("Error in Test 1 \n");
		ErrorFlag = true;
	}

	if (!(TestALU.Control("ORR", 0, 100, TestCu) == 100))
	{
		ErrorFlag = true;
		ErrorComment.append("Error in test 2\n");
	}



	return ErrorFlag;
}


bool TestCMP(ControlUnit* TestCu, ALU TestALU, std::string &ErrorComment)
{
	bool ErrorFlag = false;
	long long int TestResult;

	TestCu->setRegister(31, 0); // set CPSR to 0


	std::bitset<32> OldbCPSR = ConvertToBinary(TestCu->getRegister(31)); //Default status register state (all 0)
	TestResult = TestALU.Control("CMP", 2, 2, TestCu); //Compare 2 numbers
	std::bitset<32> NewbCPSR = ConvertToBinary(TestCu->getRegister(31)); //New statuts register state (contains output)

	if (!(OldbCPSR.test(30) != NewbCPSR.test(30))) //If there's no change and no output (expected output is 1)
	{
		ErrorFlag = true;
		ErrorComment.append("Error with CMP test 1 \n");
	}

	TestCu->setRegister(31, 0);




	OldbCPSR = ConvertToBinary(TestCu->getRegister(31));
	TestResult = TestALU.Control("CMP", 3, 2, TestCu);
	NewbCPSR = ConvertToBinary(TestCu->getRegister(31));

	if (!(OldbCPSR.test(30) == NewbCPSR.test(30)))
	{
		ErrorFlag = true;
		ErrorComment.append("Error with test 2\n");
	}

	TestCu->setRegister(31, 0);



	return ErrorFlag;
}



void RunALUTests()
{
	bool ErrorFlag = false;
	ALU TestALU;
	ControlUnit* TestCu = new ControlUnit();;
	std::string ErrorComment;

	if (TestADD(TestCu, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in ADD function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestSUB(TestCu, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in SUB function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestMUL(TestCu, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in MUL function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestAND(TestCu, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in AND function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestORR(TestCu, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in ORR function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestEOR(TestCu, TestALU, ErrorComment))
	{
		std::cout << "Error(s) in EOR function testing" << std::endl;
		std::cout << ErrorComment << std::endl;
		ErrorFlag = true;
		ErrorComment = "";
	}

	if (TestCMP(TestCu, TestALU, ErrorComment))
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

int main()
{
	//Perform Tests on ALU
	RunALUTests();



	system("Pause");
	return 0;
}
