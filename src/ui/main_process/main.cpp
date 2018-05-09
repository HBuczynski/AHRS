#include <iostream>
#include <logger/Logger.h>
#include "ProcessScheduler.h"

using namespace std;
using namespace utility;
using namespace main_process;

int main(int argc , char *argv[])
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

    ProcessScheduler scheduler;
    scheduler.run();

    return 0;
}
