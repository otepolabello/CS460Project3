#include <iostream>
#include <fstream>
#include "CodeGenerator.h"

using namespace std;

/********************************************************************************/
/* This function will generate the top piece of code that will header our file
The input is the filename and it will create a file and output the header								*/
/********************************************************************************/
CodeGen::CodeGen (string filename)
{
	string cppname = filename.substr (0, filename.length()-3) + ".cpp"; 
	cpp.open (cppname.c_str());
	cpp << "// Autogenerated Scheme to C++ Code\n";
	cpp << "// File: " << cppname << "\n";
	cpp << "#include <iostream>\n";
	cpp << "#include \"Object.h\"\n";
	cpp << "using namespace std;\n\n";
}

/********************************************************************************/
/* Destructor						       	*/
/********************************************************************************/
CodeGen::~CodeGen ()
{
	cpp.close();
}

/********************************************************************************/
/* This function will write code based of the tabs and code input.
This function is primarily called in SyntacticalAnalyzer.cpp and will be the main
code writer for our program.							*/
/********************************************************************************/
void CodeGen::WriteCode (int tabs, string code)
{
	for (int t = 0; t < tabs; t++)
		cpp << '\t';
	cpp << code;
}