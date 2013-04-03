#pragma once

#include "types.h"
#include "opcode.h"

namespace MipsJunior {
namespace Base {

class Instruction {
private:
	unsigned_value_t data;

public:
	Instruction();
	explicit Instruction(unsigned_value_t data);

	inline operator unsigned_value_t() const {
		return data;
	}

	inline Opcode GetOpcode() const {
		return Opcode(data >> 12);
	}

	inline void SetOpcode(Opcode value) {
		data = (data & 0x0FFF) | (static_cast<unsigned int>(value) << 12);
	}

	inline address_t GetTargetAddress() const {
		return data & 0x0FFF;
	}

	inline void SetTargetAddress(unsigned_value_t value) {
		data = (data & 0xF000) | (static_cast<unsigned int>(value) & 0x0FFF);
	}

	inline size_t GetRsRegister() const {
		return (data >> 10) & 0x3;
	}

	inline void SetRsRegister(size_t value) {
		data = (data & 0xF3FF) | ((static_cast<unsigned int>(value) & 0x3)  << 10);
	}

	inline size_t GetRtRegister() const {
		return (data >> 8) & 0x3;
	}

	inline void SetRtRegister(size_t value) {
		data = (data & 0xFCFF) | ((static_cast<unsigned int>(value) & 0x3) << 8);
	}

	inline size_t GetRdRegister() const {
		return (data >> 6) & 0x3;
	}

	inline void SetRdRegister(size_t value) {
		data = (data & 0xFF3F) | ((static_cast<unsigned int>(value) & 0x3) << 6);
	}

	inline AluOpcode GetAluOpcode() const {
		return AluOpcode(data & 0x3F);
	}

	inline void SetAluOpcode(AluOpcode value) {
		data = (data & 0xFFC0) | (static_cast<unsigned int>(value) & 0x3F);
	}

	inline value_t GetImmediateSigned() const {
		return value_t(static_cast<char>(data & 0xFF));
	}

	inline unsigned_value_t GetImmediateUnsigned() const {
		return data & 0xFF;
	}

	inline void SetImmediate(char value) {
		data = (data & 0xFF00) | (static_cast<unsigned_value_t>(value) & 0xFF);
	}
};
}
}
