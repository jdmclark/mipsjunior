#pragma once

#include "report.h"

namespace MipsJunior {
namespace Assembler {
namespace Diagnostics {
namespace Helper {

void FeatureNotImplemented(Report& report, const std::string& stage, const std::string& feature);
void ErrorOpeningFile(Report& report, const std::string& stage, const std::string& filename);
void UnrecognizedInput(Report& report, const std::string& stage, int line_number, const std::string& text);
void SyntaxError(Report& report, const std::string& stage, int line_number, const std::string& message);
void DuplicateLabel(Report& report, const std::string& stage, int line_number, const std::string& label);
void RegisterOutOfBounds(Report& report, const std::string& stage, int line_number);
void JumpOutOfRange(Report& report, const std::string& stage, int line_number);
void UnknownLabel(Report& report, const std::string& stage, int line_number, const std::string& label);

}
}
}
}
