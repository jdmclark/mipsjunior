#include "node.h"
#include "visitor.h"

#define ASTVISITOR_ACCEPT_IMPL( x )									\
	void MipsJunior::Assembler::AST::x::Accept(Visitor& v) {		\
		v.Visit##x(*this);											\
		return;														\
	}

MipsJunior::Assembler::AST::Node::~Node() {
	return;
}

ASTVISITOR_ACCEPT_IMPL(RTypeInstruction);
ASTVISITOR_ACCEPT_IMPL(ITypeInstruction);
ASTVISITOR_ACCEPT_IMPL(BeqInstruction);
ASTVISITOR_ACCEPT_IMPL(BneInstruction);
ASTVISITOR_ACCEPT_IMPL(JumpInstruction);
ASTVISITOR_ACCEPT_IMPL(JalInstruction);
ASTVISITOR_ACCEPT_IMPL(JrInstruction);
ASTVISITOR_ACCEPT_IMPL(LabelInstruction);
ASTVISITOR_ACCEPT_IMPL(MoveInstruction);
ASTVISITOR_ACCEPT_IMPL(ClearInstruction);
ASTVISITOR_ACCEPT_IMPL(LoadAddressInstruction);
ASTVISITOR_ACCEPT_IMPL(LoadImmediateInstruction);
ASTVISITOR_ACCEPT_IMPL(TranslationUnit);
