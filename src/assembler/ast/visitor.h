#pragma once

#include "node.h"
#include "assembler/diagnostics/report.h"

#define AVPROTO(x) virtual void Visit##x(AST::x&);
#define AVCONSUME(x) virtual void Visit##x(AST::x&) { };
#define AVDEFAULTACTION(x) void MipsJunior::Assembler::AST::Visitor::Visit##x(x& e) { DefaultAction(#x, e); }

#define ASTCLASS_TRANSLATION_UNIT(x) \
	x(TranslationUnit)

#define ASTCLASS_INSTRUCTION(x) \
	x(RTypeInstruction) \
	x(ITypeInstruction) \
	x(BeqInstruction) \
	x(BneInstruction) \
	x(JumpInstruction) \
	x(JalInstruction) \
	x(JrInstruction)

#define ASTCLASS_PSEUDO_INSTRUCTION(x) \
	x(LabelInstruction) \
	x(MoveInstruction) \
	x(ClearInstruction) \
	x(LoadAddressInstruction) \
	x(LoadImmediateInstruction)

#define ASTCLASS_ALL(x) \
	ASTCLASS_TRANSLATION_UNIT(x) \
	ASTCLASS_INSTRUCTION(x) \
	ASTCLASS_PSEUDO_INSTRUCTION(x)

namespace MipsJunior {
namespace Assembler {
namespace AST {

class Visitor {
protected:
	const std::string VisitorName;
	Diagnostics::Report& Report;
	virtual void DefaultAction(const std::string& action, Node& n);

	Visitor(const std::string& n, Diagnostics::Report& report);

public:
	virtual ~Visitor();

	ASTCLASS_ALL(AVPROTO);
};

}
}
}
