#ifndef ERROR_LOG_H
#define ERROR_LOG_H

#include "LogInterface.h"

namespace utility
{
	class ErrorLog final : public LogInterface
	{
	public:
		ErrorLog(bool writeToFile, std::string folderName);
		~ErrorLog();

		void writeMessage(const std::string &time, const std::string &message) override;
		std::string getName() override;
	};
}

#endif
