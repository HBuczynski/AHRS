#include "LogInterface.h"

using namespace std;
using namespace utility;

LogInterface::LogInterface(LogType type, bool writeToFile)
	: type_(type),
    writeToFile_(writeToFile)
{

}

LogInterface::~LogInterface()
{

}
