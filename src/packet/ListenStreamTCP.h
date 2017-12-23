#ifndef AHRS_BLACK_BOX_LISTENSTREAMTCP_H
#define AHRS_BLACK_BOX_LISTENSTREAMTCP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string>
#include <vector>
#include <memory>

#include "SendStreamTCP.h"

namespace communication
{
    class ListenStreamTCP
    {
    public:
        ListenStreamTCP(uint16_t port);
        ~ListenStreamTCP();

        void listenUsers(uint32_t userNumber);
        std::unique_ptr<SendStreamTCP> acceptUsers();

    private:
        void createSocket();

        int sock_;
        struct sockaddr_in sockAddress_;

        uint16_t port_;
        std::string address_;

    };
}
#endif //AHRS_BLACK_BOX_LISTENSTREAMTCP_H
