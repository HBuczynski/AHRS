#ifndef LOG_INTERFACE_H
#define LOG_INTERFACE_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include <time_manager/TimeManager.h>

/// Interface of the poject
namespace utility
{
	enum LogType : uint16_t
	{
		DEBUG_LOG,
		ERROR_LOG,
		WARNING_LOG,
		INFORMATION_LOG
	};

	class LogInterface
	{
	public:
		LogInterface(LogType type, bool writeToFile);
		virtual ~LogInterface();

		virtual void writeMessage(const std::string &time, const std::string &message) = 0;
		virtual std::string getName() = 0;

	protected:
		LogType type_;
		std::ofstream file_;
		bool writeToFile_;
	};
}
#endif
