#include "ErrorLog.h"

using namespace std;
using namespace utility;

ErrorLog::ErrorLog(bool writeToFile)
	: LogInterface(ERROR_LOG, writeToFile)
{
    if(writeToFile_)
    {
        string fileName = getName() + "_" + TimeManager::getTimeAndDate() + ".txt";

        file_.open(fileName.c_str());
        if (file_.fail())
        {
            logic_error("ErrorLogger: Log file was not created.");
        }
    }
}

ErrorLog::~ErrorLog()
{

}

void ErrorLog::writeMessage(const string &time, const string &message)
{
    if(writeToFile_)
    {
        file_ << time << "\t" << getName() << ":\t" << message << endl;
    }
}

string ErrorLog::getName()
{
    return string("Error");
}
