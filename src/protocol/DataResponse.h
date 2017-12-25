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
        ~DataResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

        const std::string& getData() const;

    private:
        std::string data_;
    };
}

#endif
