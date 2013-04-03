#pragma once

#include <vector>
#include <iosfwd>

#include "types.h"

namespace MipsJunior {
namespace Base {

class Memory {
private:
	std::vector<value_t> data;

	// Memory should not be copy-constructed.
	Memory(const Memory&) = delete;
	const Memory& operator=(const Memory&) = delete;

public:
	Memory();

	inline value_t Get(address_t address) const {
		return data[address];
	}

	inline void Set(address_t address, value_t value) {
		data[address] = value;
	}

	// Serializes memory to Logisim format.
	void Serialize(std::ostream& os) const;

	// Deserializes memory from Logisim format.
	void Deserialize(std::istream& is);
};

}
}
