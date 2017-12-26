#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <memory>
#include <list>
#include <utility>
#include <mutex>

namespace communication
{
    class CommunicationManager
    {
    public:
        CommunicationManager(uint16_t serverPort, uint8_t maxUserNumber);
        ~CommunicationManager();



    private:

    };
}
#endif