#include <nullunit/nullunit.h>
#include "base/memory.h"

#include <sstream>

namespace MipsJunior {
namespace Base {

BeginSuite(MemoryTests);

Case(Allocate) {
	Memory data_memory;
}

Case(Write) {
	Memory data_memory;

	data_memory.Set(10, value_t(0xFEFF));
	data_memory.Set(20, value_t(0xCDCD));
	data_memory.Set(21, value_t(0xABAB));

	Test_Assert_Eq(data_memory.Get(10), value_t(0xFEFF));
	Test_Assert_Eq(data_memory.Get(20), value_t(0xCDCD));
	Test_Assert_Eq(data_memory.Get(21), value_t(0xABAB));
}

Case(Boundaries) {
	Memory data_memory;

	data_memory.Set(0, value_t(0xFEFF));
	Test_Assert_Eq(data_memory.Get(0), value_t(0xFEFF));

	data_memory.Set(0xFFFF, value_t(0xCDCD));
	Test_Assert_Eq(data_memory.Get(0xFFFF), value_t(0xCDCD));
}

Case(SerializationTest) {
	Memory data_memory;

	data_memory.Set(4, value_t(0xFEFF));
	data_memory.Set(5, value_t(0x9199));
	data_memory.Set(509, value_t(0xCDDC));

	std::stringstream data;

	data_memory.Serialize(data);

	Test_Assert_Eq(data.str(),
		"v2.0 raw\n"
		"4*0\n"
		"feff\n"
		"9199\n"
		"503*0\n"
		"cddc\n");
}

Case(DeserializationTest) {
	Memory data_memory;

	std::string data(
		"v2.0 raw\n"
		"12*0 fabc 2 * 0 bbbb 2 * abac\n"
		"4 3 2 1 * 1 0 * 6");

	std::stringstream ss(data);

	data_memory.Deserialize(ss);

	Test_Assert_Eq(data_memory.Get(4), value_t(0));
	Test_Assert_Eq(data_memory.Get(12), value_t(0xFABC));
	Test_Assert_Eq(data_memory.Get(13), value_t(0));
	Test_Assert_Eq(data_memory.Get(14), value_t(0));
	Test_Assert_Eq(data_memory.Get(15), value_t(0xBBBB));
	Test_Assert_Eq(data_memory.Get(16), value_t(0xABAC));
	Test_Assert_Eq(data_memory.Get(17), value_t(0xABAC));
	Test_Assert_Eq(data_memory.Get(18), value_t(4));
	Test_Assert_Eq(data_memory.Get(21), value_t(1));
	Test_Assert_Eq(data_memory.Get(22), value_t(0));
}

EndSuite(MemoryTests);
}
}
