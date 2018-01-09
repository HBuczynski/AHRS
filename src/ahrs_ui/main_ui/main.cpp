#include <iostream>
#include <logger/Logger.h>


#include <packet/ListenDatagramUDP.h>
#include <packet/SendDatagramUDP.h>
#include <packet/ListenStreamTCP.h>
#include <packet/SendStreamTCP.h>
#include <ahrs_ui/communication_manager_ui/CommunicationManagerUI.h>

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


    CommunicationParameters paramters;
    paramters.sourceAddressUDP = "192.168.56.1";
    paramters.sourcePortUDP = 8000;
    paramters.destinationAddressTCP = "192.168.0.164";
    paramters.destinationPortTCP = 9000;


    CommunicationManagerUI manager(paramters);
    manager.initializeServer();
    manager.initializeClientConnection();
    manager.sendCommands();

    while(1)
    {


    }

    return 0;
}
