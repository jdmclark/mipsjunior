#include "virtualmachine.h"
#include "opcode.h"
#include "instruction.h"
#include <iostream>

MipsJunior::Base::VirtualMachine::VirtualMachine(Memory& instruction_memory, Memory& data_memory, std::ostream& display_stream)
	: pc(0), imem(instruction_memory), dmem(data_memory), display(display_stream) {
	return;
}

void MipsJunior::Base::VirtualMachine::Execute(size_t max_iterations) {
	for(size_t i = 0; i < max_iterations; ++i) {
		Instruction instr(imem.Get(pc++));

		switch(instr.GetOpcode()) {
		case Opcode::RType:
			switch(instr.GetAluOpcode()) {
			case AluOpcode::BitwiseOr:
				registers[instr.GetRdRegister()] =
					registers[instr.GetRsRegister()] | registers[instr.GetRtRegister()];
				break;

			case AluOpcode::BitwiseAnd:
				registers[instr.GetRdRegister()] =
					registers[instr.GetRsRegister()] & registers[instr.GetRtRegister()];
				break;

			case AluOpcode::Add:
				registers[instr.GetRdRegister()] =
					registers[instr.GetRsRegister()] + registers[instr.GetRtRegister()];
				break;

			case AluOpcode::Subtract:
				registers[instr.GetRdRegister()] =
					registers[instr.GetRsRegister()] - registers[instr.GetRtRegister()];
				break;

			case AluOpcode::ShiftLeft:
				registers[instr.GetRdRegister()] =
					registers[instr.GetRsRegister()] << registers[instr.GetRtRegister()];
				break;

			case AluOpcode::ShiftRightLogical:
				// HACK: compiler-dependent. Visual C++ always performs an arithmetic shift right.
				registers[instr.GetRdRegister()] = static_cast<value_t>(
					(0x0000FFFF & static_cast<int>(registers[instr.GetRsRegister()]))
					>> registers[instr.GetRtRegister()]);
				break;

			case AluOpcode::ShiftRightArithmetic:
				// HACK: compiler-dependent. Visual C++ always performs an arithmetic shift right.
				registers[instr.GetRdRegister()] =
					registers[instr.GetRsRegister()] >> registers[instr.GetRtRegister()];
				break;

			case AluOpcode::StoreLessThan:
				registers[instr.GetRdRegister()] =
					(registers[instr.GetRsRegister()] < registers[instr.GetRtRegister()]) ? 1 : 0;
				break;

			default:
				assert("Unknown ALU operation");
				break;
			}
			break;

		case Opcode::DISP:
			display << "DISP[" << std::dec << instr.GetImmediateSigned() <<
				"] = " << std::hex << registers[instr.GetRsRegister()] << std::endl;
			break;

		case Opcode::LUI:
			registers[instr.GetRtRegister()] = instr.GetImmediateSigned() << 8;
			break;

		case Opcode::ORI:
			registers[instr.GetRtRegister()] = registers[instr.GetRsRegister()] | instr.GetImmediateUnsigned();
			break;

		case Opcode::LW:
			registers[instr.GetRtRegister()] = dmem.Get(registers[instr.GetRsRegister()] + instr.GetImmediateSigned());
			break;

		case Opcode::SW:
			dmem.Set(registers[instr.GetRsRegister()] + instr.GetImmediateSigned(), registers[instr.GetRtRegister()]);
			break;

		case Opcode::ADDI:
			registers[instr.GetRtRegister()] = registers[instr.GetRsRegister()] + instr.GetImmediateSigned();
			break;

		case Opcode::ANDI:
			registers[instr.GetRtRegister()] = registers[instr.GetRsRegister()] & instr.GetImmediateUnsigned();
			break;

		case Opcode::JMP:
			pc = ((pc - 1) & address_t(0xF000)) | instr.GetTargetAddress();
			break;

		case Opcode::BEQ:
			if(registers[instr.GetRsRegister()] == registers[instr.GetRtRegister()]) {
				pc += instr.GetImmediateSigned();
			}
			break;

		case Opcode::BNE:
			if(registers[instr.GetRsRegister()] != registers[instr.GetRtRegister()]) {
				pc += instr.GetImmediateSigned();
			}
			break;

		case Opcode::JAL:
			registers[3] = pc;
			pc = ((pc - 1) & address_t(0xF000)) | instr.GetTargetAddress();
			break;

		case Opcode::JR:
			pc = registers[instr.GetRsRegister()];
			break;

		default:
			assert("Unknown instruction");
			break;
		}
	}
}
