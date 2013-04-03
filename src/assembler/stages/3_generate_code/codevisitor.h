#pragma once

#include "assembler/ast/visitor.h"
#include "base/memory.h"
#include "base/instruction.h"
#include <unordered_map>

namespace MipsJunior {
namespace Assembler {
namespace Stages {
namespace GenerateCode {

class CodeVisitor : public AST::Visitor {
protected:
	std::unordered_map<std::string, Base::address_t>& labelAddresses;
	Base::Memory& code;

	Base::address_t currentInstruction;

	void WriteInstruction(Base::Instruction instr);

public:
	CodeVisitor(Base::Memory& code, std::unordered_map<std::string, Base::address_t>& addrs,
			Diagnostics::Report& report);

private:
	AVPROTO(TranslationUnit);

	ASTCLASS_PSEUDO_INSTRUCTION(AVPROTO);
	ASTCLASS_INSTRUCTION(AVPROTO);
};

}
}
}
}
