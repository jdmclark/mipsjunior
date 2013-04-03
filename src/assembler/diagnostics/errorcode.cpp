#include "errorcode.h"

#include <iostream>
#include <iomanip>

std::ostream& MipsJunior::Assembler::Diagnostics::operator<<(std::ostream& str, ErrorCode code) {
	return str << std::setfill('0') << std::setw(4) << static_cast<int>(code);
}
