#pragma once

#include <iosfwd>

namespace MipsJunior {
namespace Assembler {
namespace Diagnostics {

enum class ErrorCode {
	// Compiler internal errors
	FeatureNotImplemented = 1000,
	ErrorOpeningFile = 1001,

	// Tokenizer errors
	UnrecognizedInput = 2000,

	// Parser errors
	SyntaxError = 3000,

	// Symbol errors
	DuplicateLabel = 4000,

	// Code generation errors
	RegisterOutOfBounds = 5000,
	JumpOutOfRange = 5001,
	UnknownLabel = 5002
};

std::ostream& operator<<(std::ostream& str, ErrorCode code);

}
}
}
