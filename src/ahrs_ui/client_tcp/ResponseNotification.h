#ifndef AHRS_RESPONSENOTIFICATION_H
#define AHRS_RESPONSENOTIFICATION_H

#include <protocol/Response.h>
#include <vector>

namespace communication
{
    class ResponseNotification
    {
    public:
        ResponseNotification();

        virtual void received(std::vector<uint8_t > responseFrame) = 0;
    };
}
#endif //AHRS_RESPONSENOTIFICATION_H
