#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include "LogInterface.h"

namespace utility
{
	class DebugLog final : public LogInterface
	{
	public:
		DebugLog(bool writeToFile, std::string folderName);
		~DebugLog();

		void writeMessage(const std::string &time, const std::string &message) override;
		std::string getName() override;

	};
}
#endif
