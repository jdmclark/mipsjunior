#include "instruction.h"

MipsJunior::Base::Instruction::Instruction()
	: data(0) {
	return;
}

MipsJunior::Base::Instruction::Instruction(unsigned_value_t value)
	: data(value) {
	return;
}
