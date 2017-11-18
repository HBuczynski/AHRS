#include "InformationLog.h"

using namespace std;
using namespace utility;

InformationLog::InformationLog(bool writeToFile, string folderName)
	: LogInterface(INFORMATION_LOG, writeToFile)
{
    if(writeToFile_)
    {
        string fileName = folderName + "/" + getName() + "_" + TimeManager::getTimeAndDate() + ".txt";

        file_.open(fileName.c_str());
        if (file_.fail())
        {
            throw logic_error("InformationLogger: Log file was not created.");
        }
    }
}


InformationLog::~InformationLog()
{

}

void InformationLog::writeMessage(const string &time, const string &message)
{
    if(writeToFile_)
    {
        file_ << time << "\t" << getName() << ":\t" << message << endl;
    }
}

string InformationLog::getName()
{
    return string("Information");
}
