#include <Logger.h>
#include <chrono>

#include "FeederScheduler.h"

using namespace std;
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

    FeederScheduler feederScheduler;

    if(feederScheduler.initialize())
    {
        feederScheduler.run();
    }
    else
    {
        if(logger.isErrorEnable())
        {
            const string message = string("-MAIN- Initialization failed !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
    }

    return 0;
}
