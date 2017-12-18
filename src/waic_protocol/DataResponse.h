#ifndef AHRS_BLACK_BOX_WAICDATARESPONSE_H
#define AHRS_BLACK_BOX_WAICDATARESPONSE_H

#include "Response.h"
#include <string>

namespace communication
{
    class DataResponse final : public Response
    {
    public:
        DataResponse(std::string dataIn);
        DataResponse(const std::vector<uint8_t>& frameBytes);
        ~DataResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

    private:
        std::string data;
    };
}

#endif
