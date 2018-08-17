#include <Logger.h>
#include <chrono>

#include "ApplicationManager.h"

using namespace std;
using namespace chrono;
using namespace utility;
using namespace main_process;

int main()
{
    Logger &logger = Logger::getInstance("FD_main");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    ApplicationManager applicationManager;

    if(applicationManager.initialize())
    {
        applicationManager.startFeederSystem();
    }
    else
    {
        if(logger.isErrorEnable())
        {
            const string message = string("main :: Initialization failed !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
    }

    return 0;
}