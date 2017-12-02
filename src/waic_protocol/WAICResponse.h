#ifndef AHRS_BLACK_BOX_WAICRESPONSE_H
#define AHRS_BLACK_BOX_WAICRESPONSE_H

#include "WAICFrame.h"

namespace communication
{
    enum WAICResponseType : uint8_t
    {
        DATA,
        ACK
    };

    class WAICResponse : public WAICFrame
    {
    public:
        WAICResponse(uint8_t dataSizeIn, WAICResponseType commandTypeIn);
        virtual ~WAICResponse();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;

        const WAICResponseType& getResponseType();

    protected:
        WAICResponseType responseType;

    };
}

#endif
