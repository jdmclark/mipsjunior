#include "instance.h"
#include <iostream>
#include <exception>

MipsJunior::Assembler::Grammar::Instance::Instance(std::istream& file, AST::Factory& ast, Diagnostics::Report& report)
	: file(file), scanner(nullptr), ReturnValue(nullptr), Factory(ast), Report(report) {
	InitScanner();
	return;
}

MipsJunior::Assembler::Grammar::Instance::~Instance() {
	DestroyScanner();
}

char MipsJunior::Assembler::Grammar::Instance::GetNext() {
	try {
		char c = file.get();
		if(file.good()) {
			return c;
		}
	}
	catch(const std::exception&) {
		return '\0';
	}

	return '\0';
}

int gra_parse(MipsJunior::Assembler::Grammar::Instance*);

MipsJunior::Assembler::AST::TranslationUnit* MipsJunior::Assembler::Grammar::Instance::Parse() {
	gra_parse(this);
	return ReturnValue;
}
