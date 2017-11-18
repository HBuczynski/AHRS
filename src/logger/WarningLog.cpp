#include "WarningLog.h"

using namespace std;
using namespace utility;

WarningLog::WarningLog(bool writeToFile, string folderName)
	: LogInterface(WARNING_LOG, writeToFile)
{
    if(writeToFile_)
    {
        string fileName = folderName + "/" + getName() + "_" + TimeManager::getTimeAndDate() + ".txt";

        file_.open(fileName.c_str());
        if (file_.fail())
        {
            throw logic_error("WarningLogger: Log file was not created.");
        }
    }
}

WarningLog::~WarningLog()
{

}

void WarningLog::writeMessage(const string &time, const string &message)
{
    if(writeToFile_)
    {
        file_ << time << "\t" << getName() << ":\t" << message << endl;
    }
}

string WarningLog::getName()
{
    return string("Warning");
}

