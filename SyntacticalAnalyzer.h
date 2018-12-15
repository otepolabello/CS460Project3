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
    token_type token;
    //HERE//
    string fileTitle;
    ofstream p2file;
    
    int program();
    int more_defines();
    int define();
    int stmt_list(const string& delim = "", const bool& print = false);
    int stmt();
    int literal();
    int quoted_lit();
    int more_tokens();
    int param_list();
    int else_part();
    int stmt_pair();
    int stmt_pair_body();
    int action();
    int any_other_token();
    //HERE//
    CodeGen* codeGen;
};

#endif
