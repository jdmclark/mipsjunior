#pragma once

#include "errorcode.h"
#include <string>

namespace MipsJunior {
namespace Assembler {
namespace Diagnostics {

class Report {
public:
	virtual ~Report();

	virtual void AddError(ErrorCode code, const std::string& stage, const std::string& reason, int line) = 0;
	virtual void AddError(ErrorCode code, const std::string& stage, const std::string& reason) = 0;

	virtual unsigned int GetErrorCount() const = 0;
};

}
}
}
