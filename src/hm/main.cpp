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
    struc.debugLog = false;
    struc.errroLog = false;
    struc.informationLog = false;
    struc.warningLog = false;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    HMManager hm;

    if (argc < 2)
    {
        if(logger.isErrorEnable())
        {
            const string message = string("-HM- :: Wrong arg !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }

        return 0;
    }

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
