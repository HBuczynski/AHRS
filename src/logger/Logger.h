#ifndef LOGGER_H
#define LOGGER_H

#include "LogInterface.h"

#include <memory>
#include <mutex>
#include <thread>
#include <map>

namespace utility
{
    struct InitLogStructure
    {
        bool writeOnConsole = true;
        bool writeLogsInSeparetFiles = true;

        bool debugLog = true;
        bool errroLog = true;
        bool informationLog = true;
        bool warningLog = true;
    };

	class Logger
	{
	public:
		static Logger &getInstance(const std::string& moduleName  = "Log");

        void initLogger(InitLogStructure logParameters);

		void writeLog(LogType type, std::string rawMessage);

		bool isInformationEnable();
		bool isDebugEnable();
		bool isErrorEnable();
		bool isWarningEnable();


		void destroy();

	private:
		Logger();
		~Logger();

		static void initFile(const std::string& moduleName);

        void registerLogType(LogType type);

		static std::mutex loggerMutex_;
		static int32_t instanceCounter_;
		static Logger *instance_;
		static std::ofstream file_;
		static std::string folderName_;
		static std::string fileName_;

		bool writeOnConsole_;
		bool writeInSeparateFiles_;

		std::map<LogType, std::shared_ptr<LogInterface> > typeRegister_;
	};
}
#endif
