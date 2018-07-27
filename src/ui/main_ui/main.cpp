#include <spawn.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <logger/Logger.h>
#include "Scheduler.h"

using namespace utility;
using namespace main_process;
using namespace std;
using namespace chrono;

extern char **environ;

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

    Scheduler processScheduler;
    processScheduler.initializeCommunicationProcesses();

    return 0;
}