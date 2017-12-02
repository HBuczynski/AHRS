#ifndef AHRS_BLACK_BOX_WAICDATARESPONSE_H
#define AHRS_BLACK_BOX_WAICDATARESPONSE_H

#include "WAICResponse.h"
#include <string>

namespace communication
{
    class WAICDataResponse final : public WAICResponse
    {
    public:
        WAICDataResponse(std::string dataIn);
        WAICDataResponse(const std::vector<uint8_t>& frameBytes);
        ~WAICDataResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

    private:
        std::string data;
    };
}

#endif
