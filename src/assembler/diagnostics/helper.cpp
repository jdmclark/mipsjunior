#include "helper.h"
#include <boost/format.hpp>

void MipsJunior::Assembler::Diagnostics::Helper::FeatureNotImplemented(Report& report, const std::string& stage, const std::string& feature) {
	report.AddError(ErrorCode::FeatureNotImplemented, stage, boost::str(boost::format("feature not implemented - %s") % feature));
}

void MipsJunior::Assembler::Diagnostics::Helper::ErrorOpeningFile(Report& report, const std::string& stage, const std::string& filename) {
	report.AddError(ErrorCode::ErrorOpeningFile, stage, boost::str(boost::format("error opening file %s") % filename));
}

void MipsJunior::Assembler::Diagnostics::Helper::UnrecognizedInput(Report& report, const std::string& stage, int line, const std::string& text) {
	report.AddError(ErrorCode::UnrecognizedInput, stage, boost::str(boost::format("unrecognized input \'%s\'") % text), line);
}

void MipsJunior::Assembler::Diagnostics::Helper::SyntaxError(Report& report, const std::string& stage, int line, const std::string& message) {
	report.AddError(ErrorCode::SyntaxError, stage, message, line);
}

void MipsJunior::Assembler::Diagnostics::Helper::DuplicateLabel(Report& report, const std::string& stage, int line, const std::string& label) {
	report.AddError(ErrorCode::DuplicateLabel, stage, boost::str(boost::format("label \'%s\' redefinition") % label), line);
}

void MipsJunior::Assembler::Diagnostics::Helper::RegisterOutOfBounds(Report& report, const std::string& stage, int line) {
	report.AddError(ErrorCode::RegisterOutOfBounds, stage, "invalid register value", line);
}

void MipsJunior::Assembler::Diagnostics::Helper::JumpOutOfRange(Report& report, const std::string& stage, int line) {
	report.AddError(ErrorCode::JumpOutOfRange, stage, "jump out of range", line);
}

void MipsJunior::Assembler::Diagnostics::Helper::UnknownLabel(Report& report, const std::string& stage, int line, const std::string& label) {
	report.AddError(ErrorCode::UnknownLabel, stage, boost::str(boost::format("undefined label \'%s\'") % label), line);
}
