#ifndef CG_H
#define CG_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

class CodeGen 
{
    public:
	CodeGen (string filename);
	~CodeGen ();
	void WriteCode (int tabs, string code);
    private:
	ofstream cpp;
};
	
#endif
