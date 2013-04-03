#include <iostream>
#include <fstream>

#include "state.h"
#include "assembler/stages/stages.h"
#include "assembler/diagnostics/streamreport.h"
#include "assembler/diagnostics/helper.h"

namespace MipsJunior {
namespace Assembler {

void PrintHelpMessage() {
	std::cout << "\nMIPS Junior Assembler\n\n";
	std::cout << "Usage: Simulator [input] [output]\n\n";
	std::cout << "Options: \n";
	std::cout << "input - The input assembly code.\n";
	std::cout << "output - The program executable, in Logisim v2.0 raw format.\n";
}

bool RunStage(Diagnostics::Report& r, AsmState& s, CompileStage cs) {
	bool retVal = (*cs)(r, s);

	if(r.GetErrorCount() > 0) {
		return false;
	}
	else {
		return retVal;
	}
}

int AsmMain(int argc, char** argv) {
	if(argc != 3) {
		PrintHelpMessage();
		return 1;
	}

	Diagnostics::StreamReport report(std::cout);
	AsmState state;

	state.InputFile = argv[1];
	state.OutputFile = argv[2];

	std::vector<CompileStage> compileStages;

	// Initialize list of stages
	compileStages.push_back(Stages::GenerateAST::GenerateAST);
	compileStages.push_back(Stages::IndexLabels::IndexLabels);
	compileStages.push_back(Stages::GenerateCode::GenerateCode);

	for(auto stage : compileStages) {
		if(!RunStage(report, state, stage)) {
			return 1;
		}
	}

	// Write code to disk
	try {
		std::ofstream of(state.OutputFile, std::ios_base::out | std::ios_base::trunc);

		state.code.Serialize(of);
	}
	catch(std::exception&) {
		Diagnostics::Helper::ErrorOpeningFile(report, "Serialization", state.OutputFile);
	}

	return 0;
}

}
}

int main(int argc, char** argv) {
	return MipsJunior::Assembler::AsmMain(argc, argv);
}
