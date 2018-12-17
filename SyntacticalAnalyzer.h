#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"
#include "CodeGenerator.h"

using namespace std;

class SyntacticalAnalyzer
{
public:
    SyntacticalAnalyzer (char * filename);
    ~SyntacticalAnalyzer ();
private:
    LexicalAnalyzer * lex;
    CodeGen * codeGen;
    token_type token;
    string fileTitle;
    ofstream p2file;
    // Transition function area
    int program();
    int more_defines(int tabs);
    int define(int tabs);
    int stmt_list(const string& delim = "", const bool& print = false, int tabs = 0);
    int stmt(int tabs = 0);
    int literal();
    int quoted_lit();
    int more_tokens();
    int param_list(const bool& first = true);
    int else_part(int tabs);
    int stmt_pair(int tabs);
    int stmt_pair_body(int tabs);
    int action(int tabs);
    int any_other_token();
};

#endif
