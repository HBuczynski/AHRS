#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include "MeasurementHandlerVisitor.h"
#include <interfaces/wireless_commands/Command.h>
#include <logger/Logger.h>
#include <packet/ListenDatagramUDP.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>

#include <map>
#include <list>
#include <atomic>
#include <memory>
#include <utility>
#include <thread>

namespace communication
{
    class CommunicationManagerUI;

    class ServerUDP
    {
    public:
        ServerUDP(uint16_t port, CommunicationManagerUI* communicationManagerUI);
        ~ServerUDP();

        void startListening();
        void stopListening();

        void registerDbParameters(uint32_t hash, const std::string& name);

    private:
        void listen();

        uint16_t port_;

        std::thread listenThread_;
        std::atomic<bool> runListenThread_;

        std::unique_ptr<ListenDatagramUDP> socket_;
        MeasuringDataFactory dataFactory_;
        MeasurementHandlerVisitor dataVisitor_;

        utility::Logger& logger_;
    };
}
#endif
