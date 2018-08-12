#include <Logger.h>
#include <chrono>

#include "ApplicationManager.h"

using namespace std;
using namespace chrono;
using namespace utility;
using namespace main_process;

int main()
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

    ApplicationManager applicationManager;

    applicationManager.initialize();
    applicationManager.launchFeederSystem();

    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    return 0;
}