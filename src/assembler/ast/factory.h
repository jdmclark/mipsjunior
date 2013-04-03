#pragma once

#include "node.h"
#include <memory>
#include <vector>

#define MAKE_NOLINES(x)							\
	x* val = new x;								\
	nodes.emplace_back(val);

#define MAKE(x)									\
	MAKE_NOLINES(x)								\
	val->NodeFirstLine = loc;

namespace MipsJunior {
namespace Assembler {
namespace AST {

class Factory {
private:
	std::vector<std::unique_ptr<Node>> nodes;

	template <typename T> class ValueStorageNode : public Node {
	public:
		ValueStorageNode() {
			return;
		}

		T Value;

		void Accept(Visitor& v) {
			return;
		}
	};

public:
	template <typename T> T* StoreValue(const T& value) {
		MAKE_NOLINES(ValueStorageNode<T>);
		val->Value = value;
		return &val->Value;
	}

	template <typename T> std::vector<T*>* MakeList(T* initial_value) {
		MAKE_NOLINES(ValueStorageNode<std::vector<T*>>);
		val->Value.push_back(initial_value);
		return &val->Value;
	}

	template <typename T> std::vector<T*>* MakeList() {
		MAKE_NOLINES(ValueStorageNode<std::vector<T*>>);
		return &val->Value;
	}

	TranslationUnit* MakeTranslationUnit(std::vector<Instruction*>* instructions, int loc);

	// Instructions
	RTypeInstruction* MakeRTypeInstruction(int rs, int rt, int rd, Base::AluOpcode function, int loc);
	ITypeInstruction* MakeITypeInstruction(int rs, int rt, Base::value_t immediate, Base::Opcode opcode, int loc);
	BeqInstruction* MakeBeqInstruction(int rs, int rt, const std::string& label, int loc);
	BneInstruction* MakeBneInstruction(int rs, int rt, const std::string& label, int loc);
	JumpInstruction* MakeJumpInstruction(const std::string& label, int loc);
	JalInstruction* MakeJalInstruction(const std::string& label, int loc);
	JrInstruction* MakeJrInstruction(int rs, int loc);

	// Pseudo-instructions
	LabelInstruction* MakeLabelInstruction(const std::string& label, Instruction* instruction, int loc);
	MoveInstruction* MakeMoveInstruction(int rs, int rt, int loc);
	ClearInstruction* MakeClearInstruction(int rt, int loc);
	LoadAddressInstruction* MakeLoadAddressInstruction(int rt, const std::string& label, int loc);
	LoadImmediateInstruction* MakeLoadImmediateInstruction(int rt, Base::value_t immediate, int loc);
};

}
}
}
