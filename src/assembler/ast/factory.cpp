#include "factory.h"
#include <string>
#include <algorithm>

using namespace MipsJunior::Assembler::AST;

TranslationUnit* Factory::MakeTranslationUnit(std::vector<Instruction*>* instructions, int loc)
{
	MAKE(TranslationUnit);
	val->instructions = instructions;
	return val;
}

RTypeInstruction* Factory::MakeRTypeInstruction(int rs, int rt, int rd, MipsJunior::Base::AluOpcode function, int loc)
{
	MAKE(RTypeInstruction);
	val->rs = rs;
	val->rt = rt;
	val->rd = rd;
	val->function = function;
	return val;
}

ITypeInstruction* Factory::MakeITypeInstruction(int rs, int rt, MipsJunior::Base::value_t immediate, MipsJunior::Base::Opcode opcode, int loc)
{
	MAKE(ITypeInstruction);
	val->rs = rs;
	val->rt = rt;
	val->immediate = immediate;
	val->opcode = opcode;
	return val;
}

BeqInstruction* Factory::MakeBeqInstruction(int rs, int rt, const std::string& label, int loc)
{
	MAKE(BeqInstruction);
	val->rs = rs;
	val->rt = rt;
	val->label = label;
	return val;
}

BneInstruction* Factory::MakeBneInstruction(int rs, int rt, const std::string& label, int loc)
{
	MAKE(BneInstruction);
	val->rs = rs;
	val->rt = rt;
	val->label = label;
	return val;
}

JumpInstruction* Factory::MakeJumpInstruction(const std::string& label, int loc)
{
	MAKE(JumpInstruction);
	val->label = label;
	return val;
}

JalInstruction* Factory::MakeJalInstruction(const std::string& label, int loc)
{
	MAKE(JalInstruction);
	val->label = label;
	return val;
}

JrInstruction* Factory::MakeJrInstruction(int rs, int loc)
{
	MAKE(JrInstruction);
	val->rs = rs;
	return val;
}

LabelInstruction* Factory::MakeLabelInstruction(const std::string& label, Instruction* instruction, int loc)
{
	MAKE(LabelInstruction);
	val->label = label;
	val->instruction = instruction;
	return val;
}

MoveInstruction* Factory::MakeMoveInstruction(int rs, int rt, int loc)
{
	MAKE(MoveInstruction);
	val->rs = rs;
	val->rt = rt;
	return val;
}

ClearInstruction* Factory::MakeClearInstruction(int rt, int loc)
{
	MAKE(ClearInstruction);
	val->rt = rt;
	return val;
}

LoadAddressInstruction* Factory::MakeLoadAddressInstruction(int rt, const std::string& label, int loc)
{
	MAKE(LoadAddressInstruction);
	val->rt = rt;
	val->label = label;
	return val;
}

LoadImmediateInstruction* Factory::MakeLoadImmediateInstruction(int rt, MipsJunior::Base::value_t immediate, int loc)
{
	MAKE(LoadImmediateInstruction);
	val->rt = rt;
	val->value = immediate;
	return val;
}
