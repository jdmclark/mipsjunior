#pragma once

#include "memory.h"
#include <iosfwd>
#include <assert.h>

namespace MipsJunior {
namespace Base {

class VirtualMachine {
private:
	value_t registers[4];
	address_t pc;
	Memory &imem, &dmem;
	std::ostream& display;

	VirtualMachine(const VirtualMachine&) = delete;
	const VirtualMachine& operator=(const VirtualMachine&) = delete;

public:
	VirtualMachine(Memory& instruction_memory, Memory& data_memory, std::ostream& display_stream);

	inline void SetRegister(size_t addr, value_t value) {
		assert(addr < 4);
		registers[addr] = value;
	}

	inline value_t GetRegister(size_t addr) const {
		assert(addr < 4);
		return registers[addr];
	}

	inline void SetProgramCounter(address_t value) {
		pc = value;
	}

	inline address_t GetProgramCounter() const {
		return pc;
	}

	void Execute(size_t max_iterations);
};
}
}
