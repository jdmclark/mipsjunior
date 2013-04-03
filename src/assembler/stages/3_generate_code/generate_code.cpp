#include "assembler/state.h"
#include "assembler/diagnostics/helper.h"
#include "codevisitor.h"

namespace MipsJunior {
namespace Assembler {
namespace Stages {
namespace GenerateCode {

bool GenerateCode(Diagnostics::Report& report, AsmState& state) {
	if(state.abstractSyntaxTree == nullptr) {
		return false;
	}

	CodeVisitor v(state.code, state.labelAddresses, report);
	state.abstractSyntaxTree->Accept(v);

	return true;
}

}
}
}
}
