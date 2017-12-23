#include <iostream>
#include <logger/Logger.h>


#include <packet/ListenDatagramUDP.h>
#include <packet/SendDatagramUDP.h>
#include <packet/ListenStreamTCP.h>
#include <packet/SendStreamTCP.h>

using namespace std;
using namespace utility;
using namespace communication;

int main(int argc , char *argv[])
{
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    if(a == 1) {
        if (b == 1) {

            ListenDatagramUDP datagram(8000);
            string msg;

            cout << "Server starts running." << endl;
            while (1) {

                auto frame = datagram.receivePacket();
                string msg(frame.begin(), frame.end()) ;

                cout << "Dostalem:  " << msg << endl;
            }

        } else {

            SendDatagramUDP client(8000, "127.0.0.1");

            cout << "Client starts running." << endl;

            while (1) {
                getchar();
                string msg("siemaneczko");
                vector<uint8_t> vec(msg.begin(), msg.end());
                client.sendData(vec);
            }

        }
    } else{
        if (b == 1) {
            cout << "Jetsem w serw." << endl;
            ListenStreamTCP server(9000);

            string msg("dziena");
            vector<uint8_t> vec(msg.begin(), msg.end());

            server.listenUsers(2);

            unique_ptr<SendStreamTCP> client = server.acceptUsers();

            cout << "Server starts running." << endl;

            while (1) {
                auto frame = client->receivePacket();
                string lol(frame.begin(), frame.end()) ;
                cout << "Dostalem" << lol << endl;

                client->sendData(vec);
            }

        } else {

            SendStreamTCP client(9000, "127.0.0.1");

            client.connectToServer();

            string msg("siemaneczko");
            vector<uint8_t> vec(msg.begin(), msg.end());

            cout << "Client starts running." << endl;

            while (1) {
                getchar();

                client.sendData(vec);
            }

        }
    }


    return 0;
}
