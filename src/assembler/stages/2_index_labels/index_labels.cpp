#include "assembler/state.h"
#include "assembler/diagnostics/helper.h"
#include "assembler/grammar/instance.h"
#include "labelvisitor.h"

namespace MipsJunior {
namespace Assembler {
namespace Stages {
namespace IndexLabels {

bool IndexLabels(Diagnostics::Report& report, AsmState& state) {
	if(state.abstractSyntaxTree == nullptr) {
		return false;
	}

	LabelVisitor v(state.labelAddresses, report);
	state.abstractSyntaxTree->Accept(v);

	return true;
}

}
}
}
}
