#include <iostream>
#include <logger/Logger.h>


#include <packet/ListenDatagramUDP.h>
#include <packet/SendDatagramUDP.h>
#include <packet/ListenStreamTCP.h>
#include <packet/SendStreamTCP.h>

#include "CommunicationManager.h"

using namespace std;
using namespace utility;
using namespace communication;

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

    CommunicationManager manager(9000,2);
    manager.initializeExternalCommmunication();

    while(1)
    {}

    return 0;
}
