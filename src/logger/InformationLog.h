#ifndef INFORMATION_LOG_H
#define INFORMATION_LOG_H

#include "LogInterface.h"

namespace utility
{
	class InformationLog final : public LogInterface
	{
	public:
		InformationLog(bool writeToFile, std::string folderName);
		~InformationLog();

		void writeMessage(const std::string &time, const std::string &message) override;
		std::string getName() override;
	};
}
#endif
