#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "assembler/ast/factory.h"
#include "base/memory.h"
#include "base/types.h"

namespace MipsJunior {
namespace Assembler {

class AsmState {
public:
	std::string InputFile;
	std::string OutputFile;

	AST::Factory astFactory;
	AST::TranslationUnit* abstractSyntaxTree;
	Base::Memory code;

	std::unordered_map<std::string, Base::address_t> labelAddresses;

	AsmState();
};

}
}
