#include <stdexcept>
#include <time_manager/TimeManager.h>

#include "Logger.h"
#include "DebugLog.h"
#include "ErrorLog.h"
#include "InformationLog.h"
#include "WarningLog.h"

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
using namespace utility;

Logger *Logger::instance_ = nullptr;
mutex Logger::loggerMutex_;
ofstream Logger::file_;
int32_t Logger::instanceCounter_ = 0;
string Logger::folderName_ = "";
string Logger::fileName_ = "";

Logger::Logger()
	: writeOnConsole_(false),
	writeInSeparateFiles_(false)
{
}

Logger::~Logger()
{
}

Logger &Logger::getInstance(const std::string& moduleName)
{
	if (!instance_)
	{
		lock_guard<mutex> lock(loggerMutex_);
		if (!instance_)
		{
			instance_ = new Logger();
			++instanceCounter_;

			initFile(moduleName);
		}
	}

	return *instance_;
}

void Logger::initFile(const std::string& moduleName)
{
    folderName_ = moduleName + "_" + TimeManager::getDate() + "_" + TimeManager::getPreciselyTime();
    mkdir(folderName_.c_str(), 0777);

	fileName_ = folderName_ + "/" + "log_" + TimeManager::getDate() + "_" + TimeManager::getPreciselyTime() + ".txt";
}

void Logger::initLogger(InitLogStructure logParameters)
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
        logInstance = make_shared<DebugLog>(writeInSeparateFiles_, folderName_);
        typeRegister_[type] = logInstance;
    }
    else if(type == ERROR_LOG)
    {
        logInstance = make_shared<ErrorLog>(writeInSeparateFiles_, folderName_);
        typeRegister_[type] = logInstance;
    }
    else if(type == WARNING_LOG)
    {
        logInstance = make_shared<WarningLog>(writeInSeparateFiles_, folderName_);
        typeRegister_[type] = logInstance;
    }
    else if(type == INFORMATION_LOG)
    {
        logInstance = make_shared<InformationLog>(writeInSeparateFiles_, folderName_);
        typeRegister_[type] = logInstance;
    }
    else
    {
        throw invalid_argument("Logger: Wrong logger_ type was registered.");
    }
}

void Logger::writeLog(LogType type, string rawMessage)
{
    // Critical section. The log handler can be shared by several threads.
    lock_guard<mutex> lock(loggerMutex_);

    file_.open(fileName_.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    if (file_.fail())
    {
        throw logic_error("Logger: Main logger_ file was not created.");
    }

	auto logHandler = typeRegister_.find(type);

	if (logHandler != typeRegister_.end())
	{
        string preciselyTime = TimeManager::getPreciselyTime();
		string message = preciselyTime + "\t#" + (logHandler->second)->getName() + ":\t" + rawMessage + "\n";

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
        throw invalid_argument("Logger: Chosen logger_ type was not registered.");
	}

    file_.close();
}

void Logger::destroy()
{
	--instanceCounter_;
	if (instance_ != nullptr && instanceCounter_ == 0)
	{
		delete instance_;
	}
}

bool Logger::isInformationEnable()
{
    if(typeRegister_.end() != typeRegister_.find(INFORMATION_LOG))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Logger::isDebugEnable()
{
    if(typeRegister_.end() != typeRegister_.find(DEBUG_LOG))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Logger::isErrorEnable()
{
    if(typeRegister_.end() != typeRegister_.find(ERROR_LOG))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Logger::isWarningEnable()
{
    if(typeRegister_.end() != typeRegister_.find(WARNING_LOG))
    {
        return true;
    }
    else
    {
        return false;
    }
}
