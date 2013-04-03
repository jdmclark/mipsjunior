#pragma once

#include "assembler/state.h"
#include "assembler/diagnostics/report.h"

namespace MipsJunior {
namespace Assembler {

typedef bool (*CompileStage)(Diagnostics::Report&, AsmState&);

namespace Stages {

namespace GenerateAST {
bool GenerateAST(Diagnostics::Report& report, AsmState& state);
}

namespace IndexLabels {
bool IndexLabels(Diagnostics::Report& report, AsmState& state);
}

namespace GenerateCode {
bool GenerateCode(Diagnostics::Report& report, AsmState& state);
}

}

}
}
