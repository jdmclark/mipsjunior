#pragma once

#include "base/types.h"
#include "assembler/ast/visitor.h"
#include <unordered_map>
#include <string>

namespace MipsJunior {
namespace Assembler {
namespace Stages {
namespace IndexLabels {

class LabelVisitor : public AST::Visitor {
protected:
	std::unordered_map<std::string, Base::address_t>& labelAddresses;

public:
	LabelVisitor(std::unordered_map<std::string, Base::address_t>& addrs, Diagnostics::Report& report);

private:
	Base::address_t currentAddress;

	AVPROTO(TranslationUnit);
	AVPROTO(LabelInstruction);
	AVPROTO(MoveInstruction);
	AVPROTO(ClearInstruction);
	AVPROTO(LoadAddressInstruction);
	AVPROTO(LoadImmediateInstruction);

	ASTCLASS_INSTRUCTION(AVPROTO);
};

}
}
}
}
