#include <stdexcept>
#include <time_manager/TimeManager.h>

#include "Logger.h"
#include "DebugLog.h"
#include "ErrorLog.h"
#include "InformationLog.h"
#include "WarningLog.h"

using namespace std;
using namespace utility;

Logger *Logger::instance_ = nullptr;
mutex Logger::loggerMutex_;
fstream Logger::file_;
int32_t Logger::instanceCounter_ = 0;

Logger::Logger()
	: writeOnConsole_(false),
	writeInSeparateFiles_(false)
{
}

Logger::~Logger()
{
}

Logger &Logger::getInstance()
{
	if (instance_ != nullptr)
	{
		lock_guard<mutex> lock(loggerMutex_);
		if (instance_ != nullptr)
		{
			instance_ = new Logger();
			++instanceCounter_;

			initFile();
		}
	}

	return *instance_;
}

void Logger::initFile()
{
	string fileName = "log_" + TimeManager::getTimeAndDate() + ".txt";

    file_.open(fileName.c_str());
    if (file_.fail())
    {
        logic_error("Logger: Main logger file was not created.");
    }
}

void Logger::initLogger(const InitLogStructure &logParameters)
{
    writeInSeparateFiles_ = logParameters.writeLogsInSeparetFiles;
    writeOnConsole_ = logParameters.writeOnConsole;

    if(logParameters.debugLog)
        registerLogType(DEBUG_LOG);

    if(logParameters.errroLog)
        registerLogType(ERROR_LOG);

    if(logParameters.warningLog)
        registerLogType(WARNING_LOG);

    if(logParameters.informationLog)
        registerLogType(INFORMATION_LOG);
}

void Logger::registerLogType(LogType type)
{
    shared_ptr<LogInterface> logInstance;

    if(type == DEBUG_LOG)
    {
        logInstance = make_shared<DebugLog>();
        typeRegister_[type] = logInstance;
    }
    else if(type == ERROR_LOG)
    {
        logInstance = make_shared<ErrorLog>();
        typeRegister_[type] = logInstance;
    }
    else if(type == WARNING_LOG)
    {
        logInstance = make_shared<WarningLog>();
        typeRegister_[type] = logInstance;
    }
    else if(type == INFORMATION_LOG)
    {
        logInstance = make_shared<InformationLog>();
        typeRegister_[type] = logInstance;
    }
    else
    {
        throw invalid_argument("Logger: Wrong logger type was registered.");
    }
}

void Logger::writeLog(LogType type, string rawMessage)
{
    // Critical section. The log handler can be shared by several threads.
    lock_guard<mutex> lock(loggerMutex_);

	auto logHandler = typeRegister_.find(type);

	if (logHandler != typeRegister_.end())
	{
        string preciselyTime = TimeManager::getPreciselyTime();
		string message = (logHandler->second)->getName();

		file_ << message;

		if(writeOnConsole_)
		{
            cout << message << endl;
		}

		if(writeInSeparateFiles_)
		{
            (logHandler->second)->writeMessage(preciselyTime, rawMessage);
		}
	}
	else
	{
        throw invalid_argument("Logger: Chosen logger type was not registered.");
	}
}

void Logger::destroy()
{
	--instanceCounter_;
	if (instance_ != nullptr && instanceCounter_ == 0)
	{
		delete instance_;
	}
}
