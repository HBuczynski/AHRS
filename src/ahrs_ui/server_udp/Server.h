#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include "DataHandlerVisitor.h"
#include <protocol/Command.h>
#include <packet/ListenDatagramUDP.h>
#include <protocol/MeasuringDataFactory.h>

#include <map>
#include <list>
#include <atomic>
#include <memory>
#include <utility>
#include <thread>

namespace communication
{
    class Server
    {
    public:
        Server(uint16_t port);
        ~Server();

        void startListening();
        void stopListening();

    private:
        void listen();

        uint16_t port_;

        std::thread listenThread_;
        std::atomic<bool> runListenThread_;

        std::unique_ptr<ListenDatagramUDP> socket_;
        MeasuringDataFactory dataFactory_;
        DataHandlerVisitor dataVisitor_;
    };
}
#endif