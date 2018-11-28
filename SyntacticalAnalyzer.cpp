#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
  string name = filename;
  lex = new LexicalAnalyzer (filename);
  string p2name = name.substr (0, name.length()-3) + ".p2";
  p2file.open(p2name);
  token_type t;
  int errors = program();
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
  delete lex;
}

int SyntacticalAnalyzer::program()
{
  int errors = 0;
  token = lex->GetToken();
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Program function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  // apply rule 1
  if (token == LPAREN_T)
    {
      p2file << "Using Rule 1\n";
      token = lex->GetToken();
      errors += define();
      if (token == LPAREN_T)
	{
	  token = lex->GetToken();
	  errors += more_defines();
	}
      else
	{
	  lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
	  errors++;
	}
      if (token == EOF_T)
	{
	  // do nothing 
	}
      else
	{
	  lex->ReportError ("EOF token expected, '" + lex->GetTokenName(token) + "' found.");
          errors++;
	}
    }
  else
    {
      lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Program function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::more_defines()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering More_Defines function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == DEFINE_T)
    { // apply rule 2
      p2file << "Using Rule 2\n";
      errors += define();
      if (token == LPAREN_T)
	{
	  token = lex->GetToken();
	  errors += more_defines();
	}
      else
	{
	  lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
          errors++;
	}
    }
 
  else if (token == IDENT_T)
    { // apply rule 3
      p2file << "Using Rule 3\n";
      token = lex->GetToken();
      errors += stmt_list();
      if (token == RPAREN_T)
	token = lex->GetToken();
      else
	{
	  lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
          errors++;
	}
    }

  if (token == EOF_T)
    { // apply rule 1
    }
  else
    {
      lex->ReportError ("IDENT_T or DEFINE_T expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
      }
  tok = lex->GetTokenName(token);
  p2file << "Exiting More_Defines function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::define()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Define function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == DEFINE_T)
    { // apply rule 4
      p2file << "Using Rule 4\n";
      token = lex->GetToken();
      if (token == LPAREN_T)
	{
	  token = lex->GetToken();
	  if (token == IDENT_T)
	    {
	      token = lex->GetToken();
	      errors += param_list();
	      if (token == RPAREN_T)
		{
		  token = lex->GetToken();
		  errors += stmt();
		  errors += stmt_list();
		  if (token == RPAREN_T)
		    token = lex->GetToken();
		  else
		    {
		      lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
		      errors++;
		    }
		}
	      else
		{
		  lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
		  errors++;
		}
	    }
	  else
	    {
	      lex->ReportError ("IDENT_T token expected, '" + lex->GetTokenName(token) + "' found.");
	      errors++;
	    }
	}
      else
	{
	  lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
          errors++;
	}
    }
  else
    {
      lex->ReportError ("DEFINE_T token expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Define function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::stmt_list()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Stmt_List function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T
      || token == IDENT_T || token == LPAREN_T)
    { // apply rule 5
      p2file << "Using Rule 5\n";
      errors += stmt();
      errors += stmt_list();
    }
  else if (token == RPAREN_T)
    { // apply rule 6
      p2file << "Using Rule 6\n";
    }
  else
    {
      lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Stmt_List function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::stmt()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Stmt function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T)
    { // apply rule 7
      p2file << "Using Rule 7\n";
      errors += literal();
    }
  else if (token == IDENT_T)
    { // apply rule 8
      p2file << "Using Rule 8\n";
      token = lex->GetToken();
    }
  else if (token == LPAREN_T)
    { // apply rule 9
      p2file << "Using Rule 9\n";
      token = lex->GetToken();
      errors += action();
      if (token == RPAREN_T)
	token = lex->GetToken();
      else
	{
	  lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
          errors++;
	}
    }
  else
    {
      lex->ReportError ("NUMLIT_T, STRLIT_T, SQUOTE_T, IDENT_T, or LPAREN_T expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Stmt function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::literal()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Literal function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == NUMLIT_T)
    { // apply rule 10
      p2file << "Using Rule 10\n";
      token = lex->GetToken();
    }
  else if (token == STRLIT_T)
    { // apply rule 11
      p2file << "Using Rule 11\n";
      token = lex->GetToken();
    }
  else if (token == SQUOTE_T)
    { // apply rule 12
      p2file << "Using Rule 12\n";
      token = lex ->GetToken();
      errors += quoted_lit();
    }
  else
    {
      lex->ReportError ("NUMLIT_T, STRLIT_T or SQUOTE_T expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Literal function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::quoted_lit()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Quoted_Lit function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token >= IDENT_T && token <= LPAREN_T || token == SQUOTE_T)
    { // apply rule 13
      p2file << "Using Rule 13\n";
      errors += any_other_token();
    }
  else
    {
      lex->ReportError ("any other token expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Quoted_Lit function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::more_tokens()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering More_Tokens function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token >= IDENT_T && token <= LPAREN_T || token == SQUOTE_T)
    { // apply rule 14
      p2file << "Using Rule 14\n";
      errors += any_other_token();
      errors += more_tokens();
    }
  else if (token == RPAREN_T)
    { // apply rule 15
      p2file << "Using Rule 15\n";
    }
  else
    {
      lex->ReportError ("any other token expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting More_Tokens function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::param_list()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Param_List function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == IDENT_T)
    { // apply rule 16
      p2file << "Using Rule 16\n";
      token = lex->GetToken();
      errors += param_list();
    }
  else if (token == RPAREN_T)
    { // apply rule 17
      p2file << "Using Rule 17\n";
    }
  else
    {
      lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Param_List function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::else_part()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Else_Part function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T
      || token == IDENT_T || token == LPAREN_T)
    { // apply rule 18
      p2file << "Using Rule 18\n";
      errors += stmt();
    }
  else if (token == RPAREN_T)
    { // apply rule 19
      p2file << "Using Rule 19\n";
    }
  else
    {
      lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Else_Part function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::stmt_pair()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Stmt_Pair function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == LPAREN_T)
    { // apply rule 20
      p2file<< "Using Rule 20\n";
      token = lex->GetToken();
      errors += stmt_pair_body();
    }
  else if (token == RPAREN_T)
    { // apply rule 21
      p2file << "Using Rule 21\n";
    }
  else
    {
      lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Stmt_Pair function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::stmt_pair_body()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Stmt_Pair_Body function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T
      || token == IDENT_T || token == LPAREN_T)
    { // apply rule 22
      p2file << "Using Rule 22\n";
      errors += stmt();
      if (token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T
	  || token == IDENT_T || token == LPAREN_T)
	{
	  errors += stmt();
	  if (token == RPAREN_T)
	    {
	      token = lex->GetToken();
	      errors += stmt_pair();
	    }
	  else
	    {
	      lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
	    }
	}
      else
	{
	  lex->ReportError ("NUMLIT_T, STRLIT_T, SQUOTE_T, IDENT_T, or LPAREN_T expected, '" + lex->GetTokenName(token) + "' found.");
	  errors++;
	}
    }
  else if (token == ELSE_T)
    { // apply rule 23
      p2file << "Using Rule 23\n";
      token = lex->GetToken();
      errors += stmt();
      if (token == RPAREN_T)
	{
	  token = lex->GetToken();
	}
    }
  else
    {
      lex->ReportError ("NUMLIT_T, STRLIT_T, SQUOTE_T, IDENT_T, LPAREN_T or ELSE_T expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Stmt_Pair_Body function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::action()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Action function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  switch(token)
    {

    case IF_T:
      // apply rule 24
      p2file << "Using Rule 24\n";
      token = lex->GetToken();
      errors += stmt();
      errors += stmt();
      errors += else_part();
      break;

    case COND_T:
      // apply rule 25
      p2file << "Using Rule 25\n";
      token = lex->GetToken();
      if (token == LPAREN_T)
	{
	  token = lex->GetToken();
	  errors += stmt_pair_body();
	}
      else
	{
	  lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
	  errors++;
	}
      break;

    // apply rules 26, 30-35, 41, 48
    case LISTOP_T:
      p2file << "Using Rule 26\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case NOT_T:
      p2file << "Using Rule 30\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case NUMBERP_T:
      p2file << "Using Rule 31\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case LISTP_T:
      p2file << "Using Rule 32\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case ZEROP_T:
      p2file << "Using Rule 33\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case NULLP_T:
      p2file << "Using Rule 34\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case STRINGP_T:
      p2file << "Using Rule 35\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case ROUND_T:
      p2file << "Using Rule 41\n";
      token = lex->GetToken();
      errors += stmt();
      break;
    case DISPLAY_T:
      p2file << "Using Rule 48\n";
      token = lex->GetToken();
      errors += stmt();
      break;

    // apply rules 27, 40
    case CONS_T:
      p2file << "Using Rule 27\n";
      token = lex->GetToken();
      errors += stmt();
      errors += stmt();
      break;
    case MODULO_T:
      p2file << "Using Rule 40\n";
      token = lex->GetToken();
      errors += stmt();
      errors += stmt();
      break;

    // apply rules 28, 29, 36, 39, 42-47
    case AND_T:
      p2file << "Using Rule 28\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case OR_T:
      p2file << "Using Rule 29\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case PLUS_T:
      p2file << "Using Rule 36\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case MULT_T:
      p2file << "Using Rule 39\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case EQUALTO_T:
      p2file << "Using Rule 42\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case GT_T:
      p2file << "Using Rule 43\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case LT_T:
      p2file << "Using Rule 44\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case GTE_T:
      p2file << "Using Rule 45\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case LTE_T:
      p2file << "Using Rule 46\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;
    case IDENT_T:
      p2file << "Using Rule 47\n";
      token = lex->GetToken();
      errors += stmt_list();
      break;

    // apply rules 37, 38
    case MINUS_T:
      p2file << "Using Rule 37\n";
      token = lex->GetToken();
      errors += stmt();
      errors += stmt_list();
      break;
    case DIV_T:
      p2file << "Using Rule 38\n";
      token = lex->GetToken();
      errors += stmt();
      errors += stmt_list();
      break;

    case NEWLINE_T:
      // apply rule 49
      p2file << "Using Rule 49\n";
      token = lex->GetToken();
      break;

    case RPAREN_T:
      // do nothing
      break;
      
    default:
      lex->ReportError ("action token expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Action function; current token is: " << tok << endl;
  return errors;
}

int SyntacticalAnalyzer::any_other_token()
{
  string tok = lex->GetTokenName(token), lexeme = lex->GetLexeme();
  p2file << "Entering Any_Other_Token function; current token is: " << tok << ", lexeme: " << lexeme << endl;
  int errors = 0;
  if (token == LPAREN_T)
    { // apply rule 50
      p2file << "Using Rule 50\n";
      token = lex->GetToken();
      errors += more_tokens();
      if (token == RPAREN_T)
	{
	  token = lex->GetToken();
	}
      else
	{
	  lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
	  errors++;
	}
    }
  else if (token >= IDENT_T && token <= LTE_T)
    { // apply rules 51-78, 80, 81
      if(token >= IDENT_T && token <= IF_T)
	p2file << "Using Rule " << token + 50 << endl;
      else if(token == COND_T)
	p2file << "Using Rule 80\n";
      else if(token >= DISPLAY_T && token <= STRINGP_T)
	p2file << "Using Rule " << token + 49 << endl;
      else if(token == MODULO_T || token == ROUND_T)
	p2file << "Using Rule " << token + 53 << endl;
      else if(token == ELSE_T)
	p2file << "Using Rule 81\n";
      else if(token >= PLUS_T && token <= MULT_T)
	p2file << "Using Rule " << token + 46 << endl;
      else if(token >= EQUALTO_T && token <= LTE_T)
	p2file << "Using Rule " << token + 48 << endl;
      token = lex->GetToken();
    }
  else if (token == SQUOTE_T)
    { // apply rule 79
      p2file << "Using Rule 79\n";
      token = lex->GetToken();
      errors += any_other_token();
    }
  else
    {
      lex->ReportError ("any other token expected, '" + lex->GetTokenName(token) + "' found.");
      errors++;
    }
  tok = lex->GetTokenName(token);
  p2file << "Exiting Any_Other_Token function; current token is: " << tok << endl;
  return errors;
}
