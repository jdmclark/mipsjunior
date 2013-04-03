#pragma once

namespace MipsJunior {
namespace Base {

enum class Opcode {
	RType = 0,
	DISP = 1,
	LUI = 2,
	ORI = 3,
	LW = 4,
	SW = 5,
	ADDI = 6,
	ANDI = 7,
	JMP = 8,
	BEQ = 9,
	BNE = 10,
	JAL = 11,
	JR = 12
};

enum class AluOpcode {
	BitwiseOr = 0,
	BitwiseAnd = 1,
	Add = 2,
	Subtract = 3,
	ShiftLeft = 4,
	ShiftRightLogical = 5,
	ShiftRightArithmetic = 6,
	StoreLessThan = 7
};

}
}
