#include "assembler/state.h"
#include "assembler/diagnostics/helper.h"
#include "assembler/grammar/instance.h"
#include <fstream>

namespace MipsJunior {
namespace Assembler {
namespace Stages {
namespace GenerateAST {

bool GenerateAST(Diagnostics::Report& report, AsmState& state) {
	try {
		std::ifstream fs(state.InputFile);
		Grammar::Instance inst(fs, state.astFactory, report);
		state.abstractSyntaxTree = inst.Parse();
	}
	catch(std::exception&) {
		Diagnostics::Helper::ErrorOpeningFile(report, "GenerateAST", state.InputFile);
		return false;
	}

	return true;
}

}
}
}
}
