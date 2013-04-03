#include "labelvisitor.h"
#include "assembler/diagnostics/helper.h"

using namespace MipsJunior::Assembler::AST;
using MipsJunior::Assembler::Stages::IndexLabels::LabelVisitor;

LabelVisitor::LabelVisitor(std::unordered_map<std::string, MipsJunior::Base::address_t>& addrs, Diagnostics::Report& report)
	: AST::Visitor("IndexLabels::LabelVisitor", report), labelAddresses(addrs), currentAddress(0) {
	return;
}

void LabelVisitor::VisitTranslationUnit(TranslationUnit& n) {
	currentAddress = 0;

	for(auto inst : *n.instructions) {
		inst->Accept(*this);
	}
}

void LabelVisitor::VisitLabelInstruction(LabelInstruction& n) {
	auto it = labelAddresses.find(n.label);

	if(it == labelAddresses.end()) {
		labelAddresses.insert(std::make_pair(n.label, currentAddress));
	}
	else {
		Diagnostics::Helper::DuplicateLabel(Report, VisitorName, n.NodeFirstLine, n.label);
	}

	// Increment current address by size of attached instruction
	n.instruction->Accept(*this);
}

void LabelVisitor::VisitMoveInstruction(MoveInstruction& n) {
	// Move is 1 instruction
	++currentAddress;
}

void LabelVisitor::VisitClearInstruction(ClearInstruction& n) {
	// Clear is 1 instruction
	++currentAddress;
}

void LabelVisitor::VisitLoadAddressInstruction(LoadAddressInstruction& n) {
	// Load address is 2 instructions
	currentAddress += 2;
}

void LabelVisitor::VisitLoadImmediateInstruction(LoadImmediateInstruction& n) {
	// Load immediate is 2 instructions
	currentAddress += 2;
}

// Visit intrinsic instructions and increment current address by 1
#define S2INTRINSICACTION(x) void LabelVisitor::Visit##x(x& e) { ++currentAddress; }
ASTCLASS_INSTRUCTION(S2INTRINSICACTION)
