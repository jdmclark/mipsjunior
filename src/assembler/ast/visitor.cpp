#include "visitor.h"
#include "assembler/diagnostics/helper.h"

MipsJunior::Assembler::AST::Visitor::Visitor(const std::string& VisitorName, Diagnostics::Report& Report)
	: VisitorName(VisitorName), Report(Report) {
	return;
}

MipsJunior::Assembler::AST::Visitor::~Visitor() {
	return;
}

void MipsJunior::Assembler::AST::Visitor::DefaultAction(const std::string& action, Node& n) {
	Diagnostics::Helper::FeatureNotImplemented(Report, VisitorName, action);
}

ASTCLASS_ALL(AVDEFAULTACTION)
