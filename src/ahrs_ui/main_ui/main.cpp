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
    CommunicationParameters paramters;
    paramters.sourceAddressUDP = "127.0.0.1";
    paramters.sourcePortUDP = 8000;
    paramters.destinationAddressTCP = "127.0.0.1";
    paramters.destinationPortTCP = 9000;


    CommunicationManagerUI manager(paramters);
    manager.initializeServer();
    manager.initializeClientConnection();
    manager.sendCommands();


    return 0;
}
