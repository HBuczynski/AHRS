#include <iostream>
#include <logger/Logger.h>


#include <packet/ListenDatagramUDP.h>
#include <packet/SendDatagramUDP.h>
#include <packet/ListenStreamTCP.h>
#include <packet/SendStreamTCP.h>

#include <ahrs_black_box/communication_manager_black_box/CommunicationManagerBlackBox.h>

using namespace std;
using namespace utility;
using namespace communication;

int main(int argc , char *argv[])
{
    CommunicationManagerBlackBox manager(9000,2);
    manager.initialize();

    return 0;
}
