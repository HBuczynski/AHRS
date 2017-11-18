#ifndef WARNING_LOG_H
#define WARNING_LOG_H

#include "LogInterface.h"

namespace utility
{
	class WarningLog final : public LogInterface
	{
	public:
		WarningLog(bool writeToFile, std::string folderName);
		~WarningLog();

		void writeMessage(const std::string &time, const std::string &message) override;
		std::string getName() override;
	};
}
#endif
