#pragma once

#include <string>
#include <vector>
#include "base/opcode.h"
#include "base/types.h"

#define ASTVISITOR_ACCEPT_ABSTRACT										\
	public:																\
	virtual void Accept(MipsJunior::Assembler::AST::Visitor& v) = 0;	\
	private:

#define ASTVISITOR_ACCEPT												\
	public:																\
	virtual void Accept(MipsJunior::Assembler::AST::Visitor& v);		\
	private:

namespace MipsJunior {
namespace Assembler {
namespace AST {

class Visitor;

class Node {
	ASTVISITOR_ACCEPT_ABSTRACT
public:
	int NodeFirstLine;

	virtual ~Node();
};

class Instruction : public Node {
	ASTVISITOR_ACCEPT_ABSTRACT
};

class RTypeInstruction : public Instruction {
	ASTVISITOR_ACCEPT
public:
	int rs, rt, rd;
	Base::AluOpcode function;
};

class ITypeInstruction : public Instruction {
	ASTVISITOR_ACCEPT
public:
	int rs, rt;
	Base::value_t immediate;
	Base::Opcode opcode;
};

class BeqInstruction : public Instruction {
	ASTVISITOR_ACCEPT
public:
	int rs, rt;
	std::string label;
};

class BneInstruction : public Instruction {
	ASTVISITOR_ACCEPT
public:
	int rs, rt;
	std::string label;
};

class JumpInstruction : public Instruction {
	ASTVISITOR_ACCEPT
public:
	std::string label;
};

class JalInstruction : public Instruction {
	ASTVISITOR_ACCEPT
public:
	std::string label;
};

class JrInstruction : public Instruction {
	ASTVISITOR_ACCEPT
public:
	int rs;
};

class PseudoInstruction : public Instruction {
	ASTVISITOR_ACCEPT_ABSTRACT
};

class LabelInstruction : public PseudoInstruction {
	ASTVISITOR_ACCEPT
public:
	std::string label;
	Instruction* instruction;
};

class MoveInstruction : public PseudoInstruction {
	ASTVISITOR_ACCEPT
public:
	int rs, rt;
};

class ClearInstruction : public PseudoInstruction {
	ASTVISITOR_ACCEPT
public:
	int rt;
};

class LoadAddressInstruction : public PseudoInstruction {
	ASTVISITOR_ACCEPT
public:
	int rt;
	std::string label;
};

class LoadImmediateInstruction : public PseudoInstruction {
	ASTVISITOR_ACCEPT
public:
	int rt;
	Base::value_t value;
};

class TranslationUnit : public Node {
	ASTVISITOR_ACCEPT
public:
	std::vector<Instruction*>* instructions;
};

}
}
}
