#ifndef AHRS_RESPONSENOTIFICATION_H
#define AHRS_RESPONSENOTIFICATION_H

#include <cstdint>
#include <vector>

namespace communication
{
    class ResponseNotification
    {
    public:
        ResponseNotification() {};
        virtual ~ResponseNotification() {};

        virtual void received(std::vector<uint8_t > responseFrame) = 0;
    };
}
#endif //AHRS_RESPONSENOTIFICATION_H
