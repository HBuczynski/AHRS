#include <iostream>
#include <memory>
#include <chrono>
#include <fstream>

#include "CommScheduler.h"

using namespace std;
using namespace chrono;
using namespace utility;
using namespace communication;

int main(int argc , char *argv[])
{
    Logger &logger = Logger::getInstance("UI_External");
    InitLogStructure struc;
    struc.debugLog = false;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;

    logger.initLogger(struc);

    if(argc < 3)
    {
        string msg("Invalid argument number");
        logger.writeLog(LogType::ERROR_LOG, msg.c_str());

        return 0;
    }

    uint8_t mode = static_cast<uint8_t >(atoi(argv[1]));
    uint8_t processNumber = static_cast<uint8_t >(atoi(argv[2]));

    if(logger.isInformationEnable())
    {
        const string message = "-ExtCOMM- Main Process: Inititialized process. Process id: " + to_string(getpid()) + ". Parent process id: " + to_string(getppid()) + "." +
                                " Mode: " + to_string(static_cast<int>(mode)) + ", Process: " + to_string(static_cast<int>(processNumber));
        logger.writeLog(LogType::INFORMATION_LOG, message);
    }

    CommScheduler commScheduler(mode, processNumber);

    if(commScheduler.initialize())
    {
        commScheduler.run();
    }
    else
    {
        if(logger.isErrorEnable())
        {
            const string message = string("-ExtCOMM-Main Process:: Initialization failed !!");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
    }

    return 0;
}
