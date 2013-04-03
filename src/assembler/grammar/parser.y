%defines
%locations
%pure-parser
%name-prefix="gra_"
%error-verbose
%verbose
%lex-param { void* scanner }
%parse-param { MipsJunior::Assembler::Grammar::Instance* instance }

%expect 0
%expect-rr 0

%{
	#include "instance.h"
	using namespace MipsJunior::Base;
%}

%union
{
	int integer;
	
	char* string;
	
	MipsJunior::Base::AluOpcode alu_opcode;
	MipsJunior::Base::Opcode opcode;
	
	MipsJunior::Assembler::AST::TranslationUnit* translation_unit;
	MipsJunior::Assembler::AST::Instruction* instruction;
	std::vector<MipsJunior::Assembler::AST::Instruction*>* instruction_list;
}

/* Operations */
%token OR AND ADD SUB SLL SRL SRA SLT DISP LUI ORI LW SW ADDI ANDI
%token JMP BEQ BNE JAL JR MOVE CLEAR LA LI

%token <string> IDENTIFIER
%token <integer> INTEGER_LITERAL

%type <integer> register_literal
%type <alu_opcode> rtype_function
%type <opcode> memory_function immediate_function

%type <translation_unit> translation_unit
%type <instruction_list> instruction_seq
%type <instruction> instruction

/* Destructors */
%destructor { free($$); } <string>

%start translation_unit

%{
	#include <sstream>
	#include <iostream>
	
	#include "assembler/diagnostics/helper.h"
	
	int gra_lex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
	
	void gra_error(YYLTYPE* locp, MipsJunior::Assembler::Grammar::Instance* inst, const char* err) {
		MipsJunior::Assembler::Diagnostics::Helper::SyntaxError(inst->Report, "Parser", locp->first_line, err);
	}
	
	#define scanner instance->GetScanner()
	#define factory instance->Factory
%}

%%

register_literal
	: '$' INTEGER_LITERAL
		{
			if($2 < 0 || $2 > 3)
			{
				MipsJunior::Assembler::Diagnostics::Helper::RegisterOutOfBounds(instance->Report, "Parser", @$.first_line);
				YYERROR;
			}

			$$ = $2;
		}
	;

rtype_function
	: OR { $$ = AluOpcode::BitwiseOr; }
	| AND { $$ = AluOpcode::BitwiseAnd; }
	| ADD { $$ = AluOpcode::Add; }
	| SUB { $$ = AluOpcode::Subtract; }
	| SLL { $$ = AluOpcode::ShiftLeft; }
	| SRL { $$ = AluOpcode::ShiftRightLogical; }
	| SRA { $$ = AluOpcode::ShiftRightArithmetic; }
	| SLT { $$ = AluOpcode::StoreLessThan; }
	;

memory_function
	: LW { $$ = Opcode::LW; }
	| SW { $$ = Opcode::SW; }
	;

immediate_function
	: ORI { $$ = Opcode::ORI; }
	| ADDI { $$ = Opcode::ADDI; }
	| ANDI { $$ = Opcode::ANDI; }
	;

translation_unit
	: instruction_seq { instance->SetReturnValue($$ = factory.MakeTranslationUnit($1, @$.first_line)); }
	| /* Blank */ { instance->SetReturnValue($$ = factory.MakeTranslationUnit(factory.MakeList<MipsJunior::Assembler::AST::Instruction>(), @$.first_line)); }
	;

instruction_seq
	: instruction_seq instruction { ($1)->push_back($2); $$ = $1; }
	| instruction { $$ = factory.MakeList<MipsJunior::Assembler::AST::Instruction>($1); }
	;

instruction
	: IDENTIFIER ':' instruction
		{ $$ = factory.MakeLabelInstruction($1, $3, @$.first_line); }
	| rtype_function register_literal ',' register_literal ',' register_literal
		{ $$ = factory.MakeRTypeInstruction($4, $6, $2, $1, @$.first_line); }
	| DISP register_literal ',' INTEGER_LITERAL
		{ $$ = factory.MakeITypeInstruction($2, 0, $4, MipsJunior::Base::Opcode::DISP, @$.first_line); }
	| immediate_function register_literal ',' register_literal ',' INTEGER_LITERAL
		{ $$ = factory.MakeITypeInstruction($4, $2, $6, $1, @$.first_line); }
	| LUI register_literal ',' INTEGER_LITERAL
		{ $$ = factory.MakeITypeInstruction(0, $2, $4, MipsJunior::Base::Opcode::LUI, @$.first_line); }
	| memory_function register_literal ',' INTEGER_LITERAL '(' register_literal ')'
		{ $$ = factory.MakeITypeInstruction($6, $2, $4, $1, @$.first_line); }
	| BEQ register_literal ',' register_literal ',' IDENTIFIER
		{ $$ = factory.MakeBeqInstruction($2, $4, $6, @$.first_line); }
	| BNE register_literal ',' register_literal ',' IDENTIFIER
		{ $$ = factory.MakeBneInstruction($2, $4, $6, @$.first_line); }
	| JMP IDENTIFIER
		{ $$ = factory.MakeJumpInstruction($2, @$.first_line); }
	| JAL IDENTIFIER
		{ $$ = factory.MakeJalInstruction($2, @$.first_line); }
	| JR register_literal
		{ $$ = factory.MakeJrInstruction($2, @$.first_line); }
	| MOVE register_literal ',' register_literal
		{ $$ = factory.MakeMoveInstruction($4, $2, @$.first_line); }
	| CLEAR register_literal
		{ $$ = factory.MakeClearInstruction($2, @$.first_line); }
	| LA register_literal ',' IDENTIFIER
		{ $$ = factory.MakeLoadAddressInstruction($2, $4, @$.first_line); }
	| LI register_literal ',' INTEGER_LITERAL
		{ $$ = factory.MakeLoadImmediateInstruction($2, $4, @$.first_line); }
	;
