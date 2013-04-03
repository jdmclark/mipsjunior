#include "codevisitor.h"
#include "assembler/diagnostics/helper.h"
#include <limits>

using namespace MipsJunior::Assembler::AST;
using MipsJunior::Assembler::Stages::GenerateCode::CodeVisitor;

CodeVisitor::CodeVisitor(MipsJunior::Base::Memory& mem,
		std::unordered_map<std::string, MipsJunior::Base::address_t>& addrs, Diagnostics::Report& report)
	: AST::Visitor("GenerateCode::CodeVisitor", report), labelAddresses(addrs), code(mem), currentInstruction(0) {
	return;
}

void CodeVisitor::WriteInstruction(MipsJunior::Base::Instruction instr) {
	code.Set(currentInstruction++, static_cast<MipsJunior::Base::value_t>(instr));
}

void CodeVisitor::VisitTranslationUnit(TranslationUnit& n) {
	currentInstruction = 0;

	for(auto instr : *n.instructions) {
		instr->Accept(*this);
	}
}

void CodeVisitor::VisitLabelInstruction(LabelInstruction& n) {
	n.instruction->Accept(*this);
}

void CodeVisitor::VisitMoveInstruction(MoveInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::ADDI);
	instr.SetRsRegister(n.rs);
	instr.SetRtRegister(n.rt);
	instr.SetImmediate(0);

	WriteInstruction(instr);
}

void CodeVisitor::VisitClearInstruction(ClearInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::ANDI);
	instr.SetRsRegister(n.rt);
	instr.SetRtRegister(n.rt);
	instr.SetImmediate(0);

	WriteInstruction(instr);
}

void CodeVisitor::VisitLoadAddressInstruction(LoadAddressInstruction& n) {
	Base::Instruction instra;
	instra.SetOpcode(Base::Opcode::LUI);
	instra.SetRsRegister(0);
	instra.SetRtRegister(n.rt);

	Base::Instruction instrb;
	instrb.SetOpcode(Base::Opcode::ORI);
	instrb.SetRsRegister(n.rt);
	instrb.SetRtRegister(n.rt);

	// Find label
	auto it = labelAddresses.find(n.label);
	if(it == labelAddresses.end()) {
		Diagnostics::Helper::UnknownLabel(Report, VisitorName, n.NodeFirstLine, n.label);
	}
	else {
		instra.SetImmediate(static_cast<char>(it->second >> 8));
		instrb.SetImmediate(static_cast<char>(it->second));
	}

	WriteInstruction(instra);
	WriteInstruction(instrb);
}

void CodeVisitor::VisitLoadImmediateInstruction(LoadImmediateInstruction& n) {
	Base::Instruction instra;
	instra.SetOpcode(Base::Opcode::LUI);
	instra.SetRsRegister(0);
	instra.SetRtRegister(n.rt);
	instra.SetImmediate(static_cast<char>(n.value >> 8));

	Base::Instruction instrb;
	instrb.SetOpcode(Base::Opcode::ORI);
	instrb.SetRsRegister(n.rt);
	instrb.SetRtRegister(n.rt);
	instrb.SetImmediate(static_cast<char>(n.value));

	WriteInstruction(instra);
	WriteInstruction(instrb);
}

void CodeVisitor::VisitRTypeInstruction(RTypeInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::RType);
	instr.SetRsRegister(n.rs);
	instr.SetRtRegister(n.rt);
	instr.SetRdRegister(n.rd);
	instr.SetAluOpcode(n.function);

	WriteInstruction(instr);
}

void CodeVisitor::VisitITypeInstruction(ITypeInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(n.opcode);
	instr.SetRsRegister(n.rs);
	instr.SetRtRegister(n.rt);
	instr.SetImmediate(static_cast<char>(n.immediate));

	WriteInstruction(instr);
}

void CodeVisitor::VisitBeqInstruction(BeqInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::BEQ);
	instr.SetRsRegister(n.rs);
	instr.SetRtRegister(n.rt);

	// Find label
	auto it = labelAddresses.find(n.label);
	if(it == labelAddresses.end()) {
		Diagnostics::Helper::UnknownLabel(Report, VisitorName, n.NodeFirstLine, n.label);
	}
	else {
		int offset = it->second - currentInstruction - 1;

		if(offset < std::numeric_limits<char>::min() ||
			offset > std::numeric_limits<char>::max()) {
			Diagnostics::Helper::JumpOutOfRange(Report, VisitorName, n.NodeFirstLine);
		}
		else {
			instr.SetImmediate(static_cast<char>(offset));
		}
	}

	WriteInstruction(instr);
}

void CodeVisitor::VisitBneInstruction(BneInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::BNE);
	instr.SetRsRegister(n.rs);
	instr.SetRtRegister(n.rt);

	// Find label
	auto it = labelAddresses.find(n.label);
	if(it == labelAddresses.end()) {
		Diagnostics::Helper::UnknownLabel(Report, VisitorName, n.NodeFirstLine, n.label);
	}
	else {
		int offset = it->second - currentInstruction - 1;

		if(offset < std::numeric_limits<char>::min() ||
			offset > std::numeric_limits<char>::max()) {
			Diagnostics::Helper::JumpOutOfRange(Report, VisitorName, n.NodeFirstLine);
		}
		else {
			instr.SetImmediate(static_cast<char>(offset));
		}
	}

	WriteInstruction(instr);
}

void CodeVisitor::VisitJumpInstruction(JumpInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::JMP);

	// Find label
	auto it = labelAddresses.find(n.label);
	if(it == labelAddresses.end()) {
		Diagnostics::Helper::UnknownLabel(Report, VisitorName, n.NodeFirstLine, n.label);
	}
	else {
		// Test to see if appending will work.
		if((currentInstruction & 0xFF00) != (it->second & 0xFF00)) {
			Diagnostics::Helper::JumpOutOfRange(Report, VisitorName, n.NodeFirstLine);
		}
		else {
			instr.SetTargetAddress(it->second);
		}
	}

	WriteInstruction(instr);
}

void CodeVisitor::VisitJalInstruction(JalInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::JAL);

	// Find label
	auto it = labelAddresses.find(n.label);
	if(it == labelAddresses.end()) {
		Diagnostics::Helper::UnknownLabel(Report, VisitorName, n.NodeFirstLine, n.label);
	}
	else {
		// Test to see if appending will work.
		if((currentInstruction & 0xFF00) != (it->second & 0xFF00)) {
			Diagnostics::Helper::JumpOutOfRange(Report, VisitorName, n.NodeFirstLine);
		}
		else {
			instr.SetTargetAddress(it->second);
		}
	}

	WriteInstruction(instr);
}

void CodeVisitor::VisitJrInstruction(JrInstruction& n) {
	Base::Instruction instr;
	instr.SetOpcode(Base::Opcode::JR);
	instr.SetRsRegister(n.rs);

	WriteInstruction(instr);
}
