#include "streamreport.h"
#include <iostream>

MipsJunior::Assembler::Diagnostics::StreamReport::StreamReport(std::ostream& str)
	: errorCount(0), str(str) {
	return;
}

void MipsJunior::Assembler::Diagnostics::StreamReport::AddError(ErrorCode code, const std::string& stage, const std::string& reason, int line) {
	str << "Error " << code << " on line " << line << ": " << reason << " [" << stage << "]" << std::endl;
	++errorCount;
}

void MipsJunior::Assembler::Diagnostics::StreamReport::AddError(ErrorCode code, const std::string& stage, const std::string& reason) {
	str << "Error " << code << ": " << reason << " [" << stage << "]" << std::endl;
	++errorCount;
}

unsigned int MipsJunior::Assembler::Diagnostics::StreamReport::GetErrorCount() const {
	return errorCount;
}
