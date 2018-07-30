#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include "ServerTCP.h"
#include "ClientUDP.h"

#include <memory>
#include <utility>
#include <mutex>

namespace communication
{
    class ProcessManager
    {
    public:
        ProcessManager(uint16_t serverPort, uint8_t maxUserNumber);
        ~ProcessManager();

        void initializeExternalCommmunication();
        void initializeMessageQueueCommunication();
        void initializeSharedMemoryCommunication();

    private:

        std::shared_ptr<ServerTCP> server_;
        std::shared_ptr<ClientUDPManager> clientUDPManager_;
    };
}
#endif