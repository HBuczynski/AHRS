#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include <interfaces/wireless_commands/Command.h>
#include <logger/Logger.h>
#include <packet/ListenDatagramUDP.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>

#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <config_reader/FeederParameters.h>

#include <atomic>
#include <memory>
#include <thread>

namespace communication
{
    class CommunicationManagerUI;

    class EthServerUDP
    {
    public:
        EthServerUDP(uint16_t port);
        ~EthServerUDP();

        void startListening();
        void stopListening();

        void initializeSharedMemory();

    private:
        void listen();

        uint16_t port_;

        std::thread listenThread_;
        std::atomic<bool> runListenThread_;

        std::unique_ptr<ListenDatagramUDP> socket_;

        config::FeederSharedMemory sharedMemoryParameters_;
        std::unique_ptr<communication::SharedMemoryWrapper> internalSharedMemory_;
        utility::Logger& logger_;
    };
}
#endif
