#include <nullunit/nullunit.h>
#include "base/virtualmachine.h"
#include "base/instruction.h"

#include <sstream>
#include <string>

namespace MipsJunior {
namespace Base {

class VirtualMachineTestsFixture : public NullUnit::Fixture {
public:
	Memory code;
	Memory data;
	VirtualMachine vm;
	std::stringstream ss;

	VirtualMachineTestsFixture() : vm(code, data, ss)
	{
		return;
	}

	void Setup()
	{
		ss.clear();
		vm.SetProgramCounter(0);
	}
};

BeginSuiteFixture(VirtualMachineTests, VirtualMachineTestsFixture);

Case(BitwiseOr) {
	Instruction instr;
	instr.SetOpcode(Opcode::RType);
	instr.SetRsRegister(3);
	instr.SetRtRegister(2);
	instr.SetRdRegister(1);
	instr.SetAluOpcode(AluOpcode::BitwiseOr);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, 0x0F0F);
	vm.SetRegister(2, 0x0FF0);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(1), value_t(0x0FFF));
}

Case(BitwiseAnd) {
	Instruction instr;
	instr.SetOpcode(Opcode::RType);
	instr.SetRsRegister(3);
	instr.SetRtRegister(2);
	instr.SetRdRegister(1);
	instr.SetAluOpcode(AluOpcode::BitwiseAnd);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, 0x0F0F);
	vm.SetRegister(2, 0x0FF0);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(1), value_t(0x0F00));
}

Case(Add) {
	Instruction instr;
	instr.SetOpcode(Opcode::RType);
	instr.SetRsRegister(3);
	instr.SetRtRegister(2);
	instr.SetRdRegister(1);
	instr.SetAluOpcode(AluOpcode::Add);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, 0x0F0F);
	vm.SetRegister(2, 0x0001);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(1), value_t(0x0F10));
}

Case(Subtract) {
	Instruction instr;
	instr.SetOpcode(Opcode::RType);
	instr.SetRsRegister(3);
	instr.SetRtRegister(2);
	instr.SetRdRegister(1);
	instr.SetAluOpcode(AluOpcode::Subtract);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, 0x0F10);
	vm.SetRegister(2, 0x0001);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(1), value_t(0x0F0F));
}

Case(ShiftLeft) {
	Instruction instr;
	instr.SetOpcode(Opcode::RType);
	instr.SetRsRegister(3);
	instr.SetRtRegister(2);
	instr.SetRdRegister(1);
	instr.SetAluOpcode(AluOpcode::ShiftLeft);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, 0x0F0F);
	vm.SetRegister(2, 0x0004);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(1), value_t(0xF0F0));
}

Case(ShiftRightLogical) {
	Instruction instr;
	instr.SetOpcode(Opcode::RType);
	instr.SetRsRegister(3);
	instr.SetRtRegister(2);
	instr.SetRdRegister(1);
	instr.SetAluOpcode(AluOpcode::ShiftRightLogical);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, value_t(0xFFFF));
	vm.SetRegister(2, 0x0004);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(1), value_t(0x0FFF));
}

Case(ShiftRightArithmetic) {
	Instruction instr;
	instr.SetOpcode(Opcode::RType);
	instr.SetRsRegister(3);
	instr.SetRtRegister(2);
	instr.SetRdRegister(1);
	instr.SetAluOpcode(AluOpcode::ShiftRightArithmetic);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, value_t(0xFF00));
	vm.SetRegister(2, 0x0004);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(1), value_t(0xFFF0));
}

Case(Disp) {
	Instruction instr;
	instr.SetOpcode(Opcode::DISP);
	instr.SetRsRegister(3);
	instr.SetImmediate(1);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(3, value_t(0xABAB));

	vm.Execute(1);

	std::string output;
	std::getline(ss, output);

	Test_Assert_Eq(output, "DISP[1] = abab");
}

Case(Lui) {
	Instruction instr;
	instr.SetOpcode(Opcode::LUI);
	instr.SetRtRegister(2);
	instr.SetImmediate(0xAB);

	code.Set(0, static_cast<value_t>(instr));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(2), value_t(0xAB00));
}

Case(Ori) {
	Instruction instr;
	instr.SetOpcode(Opcode::ORI);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(0xFF);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, value_t(0xEAB0));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(2), value_t(0xEAFF));
}

Case(Lw) {
	Instruction instr;
	instr.SetOpcode(Opcode::LW);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(4);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, 10);
	data.Set(address_t(14), value_t(0xEEAB));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(2), value_t(0xEEAB));
}

Case(Sw) {
	Instruction instr;
	instr.SetOpcode(Opcode::SW);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(4);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, 10);
	vm.SetRegister(2, value_t(0xFFAF));

	vm.Execute(1);

	Test_Assert_Eq(data.Get(14), value_t(0xFFAF));
}

Case(Addi) {
	Instruction instr;
	instr.SetOpcode(Opcode::ADDI);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(0x01);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, value_t(0x0F0F));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(2), value_t(0x0F10));
}

Case(Andi) {
	Instruction instr;
	instr.SetOpcode(Opcode::ANDI);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(0xFF);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, value_t(0xF0F0));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetRegister(2), value_t(0x00F0));
}

Case(Jmp) {
	Instruction instr;
	instr.SetOpcode(Opcode::JMP);
	instr.SetTargetAddress(0x0CCC);

	code.Set(address_t(0xAFFF), static_cast<value_t>(instr));
	vm.SetProgramCounter(address_t(0xAFFF));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetProgramCounter(), address_t(0xACCC));
}

Case(BeqSuccess) {
	Instruction instr;
	instr.SetOpcode(Opcode::BEQ);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(2);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, 0x0CCD);
	vm.SetRegister(2, 0x0CCD);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetProgramCounter(), address_t(3));
}

Case(BeqFailure) {
	Instruction instr;
	instr.SetOpcode(Opcode::BEQ);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(2);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, 0x0CCD);
	vm.SetRegister(2, 0x0ACD);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetProgramCounter(), address_t(1));
}

Case(BneSuccess) {
	Instruction instr;
	instr.SetOpcode(Opcode::BNE);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(2);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, 0x0CCD);
	vm.SetRegister(2, 0x0ACD);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetProgramCounter(), address_t(3));
}

Case(BneFailure) {
	Instruction instr;
	instr.SetOpcode(Opcode::BNE);
	instr.SetRsRegister(1);
	instr.SetRtRegister(2);
	instr.SetImmediate(2);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(1, 0x0CCD);
	vm.SetRegister(2, 0x0CCD);

	vm.Execute(1);

	Test_Assert_Eq(vm.GetProgramCounter(), address_t(1));
}

Case(Jal) {
	Instruction instr;
	instr.SetOpcode(Opcode::JAL);
	instr.SetTargetAddress(0x0CCC);

	code.Set(address_t(0xAFFF), static_cast<value_t>(instr));
	vm.SetProgramCounter(address_t(0xAFFF));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetProgramCounter(), address_t(0xACCC));
	Test_Assert_Eq(static_cast<address_t>(vm.GetRegister(3)), address_t(0xB000));
}

Case(Jr) {
	Instruction instr;
	instr.SetOpcode(Opcode::JR);
	instr.SetRsRegister(2);

	code.Set(0, static_cast<value_t>(instr));

	vm.SetRegister(2, address_t(0xFEFF));

	vm.Execute(1);

	Test_Assert_Eq(vm.GetProgramCounter(), address_t(0xFEFF));
}


EndSuite(VirtualMachineTests);

}
}
