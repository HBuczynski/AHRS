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
        bool writeOnConsole = false;
        bool writeLogsInSeparetFiles = false;

        bool debugLog = false;
        bool errroLog = false;
        bool informationLog = false;
        bool warningLog = false;
    };

	class Logger
	{
	public:
		static Logger &getInstance();

        void initLogger(InitLogStructure logParameters);

		void writeLog(LogType type, std::string rawMessage);

		void destroy();

	private:
		Logger();
		~Logger();

		static void initFile();

        void registerLogType(LogType type);

		static std::mutex loggerMutex_;
		static int32_t instanceCounter_;
		static Logger *instance_;
		static std::ofstream file_;
		static std::string folderName;

		bool writeOnConsole_;
		bool writeInSeparateFiles_;

		std::map<LogType, std::shared_ptr<LogInterface> > typeRegister_;
	};
}
#endif
