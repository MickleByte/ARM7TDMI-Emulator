#include "pch.h"
#include "ControlUnit.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

void main()
{
	ControlUnit CU;

	vector<string> File = CU.ReadFile("thing.txt");
	CU.Decode(File);
}