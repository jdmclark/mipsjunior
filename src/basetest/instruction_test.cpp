#include "base/instruction.h"
#include <nullunit/nullunit.h>

namespace MipsJunior {
namespace Base {

BeginSuite(InstructionTests);

Case(RTypeInstruction) {
	// Create a new instruction, fill with garbage
	Instruction i(value_t(0xFEFE));

	i.SetOpcode(Opcode::RType);
	i.SetRsRegister(0);
	i.SetRtRegister(1);
	i.SetRdRegister(2);
	i.SetAluOpcode(AluOpcode::ShiftRightArithmetic);

	Test_Assert_Eq(i.GetOpcode(), Opcode::RType);
	Test_Assert_Eq(i.GetRsRegister(), 0);
	Test_Assert_Eq(i.GetRtRegister(), 1);
	Test_Assert_Eq(i.GetRdRegister(), 2);
	Test_Assert_Eq(i.GetAluOpcode(), AluOpcode::ShiftRightArithmetic);

	Test_Assert_Eq(static_cast<value_t>(i), value_t(0x186));
}

Case(ITypeInstruction) {
	// Create a new instruction, fill with garbage
	Instruction i(value_t(0xFEFE));

	i.SetOpcode(Opcode::ANDI);
	i.SetRsRegister(3);
	i.SetRtRegister(0);
	i.SetImmediate(char(0xAC));

	Test_Assert_Eq(i.GetOpcode(), Opcode::ANDI);
	Test_Assert_Eq(i.GetRsRegister(), 3);
	Test_Assert_Eq(i.GetRtRegister(), 0);
	Test_Assert_Eq(i.GetImmediateUnsigned(), 172);
	Test_Assert_Eq(i.GetImmediateSigned(), -84);

	Test_Assert_Eq(static_cast<value_t>(i), value_t(0x7CAC));
}

Case(JTypeInstruction) {
	// Create a new instruction, fill with garbage
	Instruction i(value_t(0xFEFE));

	i.SetOpcode(Opcode::JMP);
	i.SetTargetAddress(0x0DCD);

	Test_Assert_Eq(i.GetOpcode(), Opcode::JMP);
	Test_Assert_Eq(i.GetTargetAddress(), value_t(0x0DCD));

	Test_Assert_Eq(static_cast<value_t>(i), value_t(0x8DCD));
}

EndSuite(InstructionTests);

}
}
