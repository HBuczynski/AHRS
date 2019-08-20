#include <iostream>
#include <chrono>
#include <logger/Logger.h>

#include "Scheduler.h"

using namespace std;
using namespace utility;
using namespace communication;

int main(int argc , char *argv[])
{
    Logger &logger = Logger::getInstance("FD_External_comm");

    InitLogStructure struc;
    struc.debugLog = false;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    Scheduler scheduler;

    if(scheduler.initialize())
    {
        scheduler.run();
    }
    else
    {
        if(logger.isErrorEnable())
        {
            const string message = string("-EXTCOM-  Initialization failed !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
    }

    return 0;
}
