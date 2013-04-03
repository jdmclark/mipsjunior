%option reentrant
%option never-interactive
%option bison-bridge
%option bison-locations
%option yylineno
%option noyywrap
%option prefix="gra_"

%{
	#include "base/opcode.h"
	#include "instance.h"
	#include "parser.hpp"
	#include "assembler/diagnostics/helper.h"
	
	#include <string.h>	
	#include <sstream>
	#include <boost/lexical_cast.hpp>
	
	#define YY_EXTRA_TYPE MipsJunior::Assembler::Grammar::Instance*
	#define YY_USER_ACTION yylloc->first_line = yylineno;
	
	#define YY_INPUT(buf, result, max_size) {			\
		buf[0] = yyextra->GetNext();					\
		if(buf[0] == '\0') result = YY_NULL;			\
		else result = 1;								\
	}
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+

%%

#.*			/* eat line comments */

"OR"		{ return OR; }
"AND"		{ return AND; }
"ADD"		{ return ADD; }
"SUB"		{ return SUB; }
"SLL"		{ return SLL; }
"SRL"		{ return SRL; }
"SRA"		{ return SRA; }
"SLT"		{ return SLT; }
"DISP"		{ return DISP; }
"LUI"		{ return LUI; }
"ORI"		{ return ORI; }
"LW"		{ return LW; }
"SW"		{ return SW; }
"ADDI"		{ return ADDI; }
"ANDI"		{ return ANDI; }
"J"			{ return JMP; }
"BEQ"		{ return BEQ; }
"BNE"		{ return BNE; }
"JAL"		{ return JAL; }
"JR"		{ return JR; }

"MOVE"		{ return MOVE; }
"CLEAR"		{ return CLEAR; }
"LA"		{ return LA; }
"LI"		{ return LI; }

","			{ return ','; }
":"			{ return ':'; }
"("			{ return '('; }
")"			{ return ')'; }
"$"			{ return '$'; }

{L}({L}|{D})*	{ yylval->string = strdup(yytext); return IDENTIFIER; }

0[xX]{H}+	{
				std::stringstream cstrm;
				cstrm << yytext;
				cstrm >> std::hex >> yylval->integer;
				return INTEGER_LITERAL;
			}

-?{D}+		{ yylval->integer = boost::lexical_cast<int, char*>(yytext); return INTEGER_LITERAL; }

[[:space:]] /* ignore */

.			{ MipsJunior::Assembler::Diagnostics::Helper::UnrecognizedInput(yyextra->Report, "Lexer", yylineno, yytext); }

%%

void MipsJunior::Assembler::Grammar::Instance::InitScanner()
{
	yylex_init(&scanner);
	yyset_extra(this, scanner);
}

void MipsJunior::Assembler::Grammar::Instance::DestroyScanner()
{
	yylex_destroy(scanner);
}
