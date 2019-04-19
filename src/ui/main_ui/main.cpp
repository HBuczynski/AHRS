#include <string.h>

#include <logger/Logger.h>
#include "UIScheduler.h"

using namespace std;
using namespace utility;

int main(int argc, char *argv[])
{
    Logger &logger = Logger::getInstance("UI_MAIN");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    UIScheduler uiScheduler;

    if(uiScheduler.initialize())
    {
        uiScheduler.run();
    }
    else
    {
        if(logger.isErrorEnable())
        {
            const string message = string("Main UI :: Initialization failed !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
    }

    return 0;
}
