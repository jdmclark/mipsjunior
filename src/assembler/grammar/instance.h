#pragma once

#include "assembler/ast/factory.h"
#include "assembler/diagnostics/report.h"
#include <iosfwd>

namespace MipsJunior {
namespace Assembler {
namespace Grammar {

class Instance {
private:
	std::istream& file;

	// Scanner initialization members.
	// Implemented in lexer.lex.
	void InitScanner();
	void DestroyScanner();

	void* scanner;

	AST::TranslationUnit* ReturnValue;

public:
	AST::Factory& Factory;
	Diagnostics::Report& Report;

	Instance(std::istream& file, AST::Factory& ast, Diagnostics::Report& report);
	~Instance();

	char GetNext();
	AST::TranslationUnit* Parse();

	inline void* GetScanner() const {
		return scanner;
	}

	inline void SetReturnValue(AST::TranslationUnit* astroot) {
		ReturnValue = astroot;
	}
};

}
}
}
