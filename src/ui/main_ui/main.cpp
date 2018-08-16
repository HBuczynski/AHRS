#include <spawn.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <logger/Logger.h>
#include "UIApplicationManager.h"

using namespace std;
using namespace chrono;
using namespace utility;
using namespace main_process;

int main(int argc, char *argv[])
{
    Logger &logger = Logger::getInstance();

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;

    logger.initLogger(struc);

    UIApplicationManager applicationManager;

    if(applicationManager.initialize())
    {
        applicationManager.run();

        while(true)
        {

        }
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