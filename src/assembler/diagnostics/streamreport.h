#pragma once

#include "report.h"
#include <iosfwd>

namespace MipsJunior {
namespace Assembler {
namespace Diagnostics {

class StreamReport : public Report {
private:
	unsigned int errorCount;
	std::ostream& str;

public:
	StreamReport(std::ostream& str);

	void AddError(ErrorCode code, const std::string& stage, const std::string& reason, int line);
	void AddError(ErrorCode code, const std::string& stage, const std::string& reason);

	unsigned int GetErrorCount() const;
};

}
}
}
