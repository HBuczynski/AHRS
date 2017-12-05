#include <iostream>
#include <logger/Logger.h>

#include <waic_packet/WAICStreamTCP.h>
#include <waic_packet/WAICDatagramUDP.h>

using namespace std;
using namespace utility;
using namespace communication;

int main(int argc , char *argv[])
{
    /*Logger &log = Logger::getInstance();

    InitLogStructure struc;

    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;

    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;

    log.initLogger(struc);

    log.writeLog(INFORMATION_LOG, "Logger testing");*/

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    if(a == 1) {
        if (b == 1) {

            WAICDatagramUDP datagram(SERVER, 8000);
            string msg;

            cout << "Server starts running." << endl;
            while (1) {
                datagram.receivePacket(msg);

                cout << "Dostalem" << msg << endl;
            }

        } else {

            WAICDatagramUDP client(CLIENT, 8000, "127.0.0.1");

            cout << "Client starts running." << endl;

            while (1) {
                getchar();

                client.sendPacket("siemaneczko");
            }

        }
    } else{
        if (b == 1) {
            cout << "Jetsem w serw." << endl;
            WAICStreamTCP server(SERVER, 8000);
            string msg;

            server.listenUsers(2);
            shared_ptr<WAICStreamTCP> newClient = make_shared<WAICStreamTCP>();
            server.acceptUsers(newClient);

            cout << "Server starts running." << endl;

            while (1) {
                newClient->receivePacket(msg);

                cout << "Dostalem" << msg << endl;
            }

        } else {

            WAICStreamTCP client(CLIENT, 8000, "127.0.0.1");

            client.connectToServer();

            cout << "Client starts running." << endl;

            while (1) {
                getchar();

                client.sendPacket("siemaneczko");
            }

        }
    }


    return 0;
}
