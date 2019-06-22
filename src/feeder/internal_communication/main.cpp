#include <logger/Logger.h>

#include "InterManager.h"

using namespace std;
using namespace utility;
using namespace chrono;

int main(int argc , char *argv[])
{
    Logger &logger = Logger::getInstance("FD_Internal_comm");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    communication::InterManager interManager;

    if(interManager.initialize())
    {
        interManager.startCommunication();
    }
    else
    {
        if(logger.isErrorEnable())
        {
            const string message = string("-INTCOM- Initialization failed !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
    }


    return 0;
}
