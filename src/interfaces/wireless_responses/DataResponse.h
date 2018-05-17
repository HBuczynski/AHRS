#ifndef AHRS_BLACK_BOX_WAICDATARESPONSE_H
#define AHRS_BLACK_BOX_WAICDATARESPONSE_H

#include "Response.h"
#include <string>

namespace communication
{
    class DataResponse final : public Response
    {
    public:
        DataResponse(const std::string& data);
        ~DataResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        void setData(const std::string& data);
        const std::string& getData() const;

    private:
        virtual void initializeDataSize() override;

        std::string data_;
    };
}

#endif
