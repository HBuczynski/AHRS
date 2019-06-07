#include <string.h>

#include "HMManager.h"
#include <logger/Logger.h>

using namespace std;
using namespace hm;
using namespace utility;

int main(int argc, char *argv[])
{
    Logger &logger = Logger::getInstance("HM");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    HMManager hm;

    if(hm.initialize(argv[1]))
    {
        hm.run();
    }
    else
    {
        if(logger.isErrorEnable())
        {
            const string message = string("-HM- :: Initialization failed !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
    }
    return 0;
}
