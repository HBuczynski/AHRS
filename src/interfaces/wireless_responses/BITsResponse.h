#ifndef AHRS_BITSRESPONSE_H
#define AHRS_BITSRESPONSE_H

#include "Response.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    struct BitsInformation
    {
        uint8_t mode;
        uint8_t progress;

        uint8_t communication;
        uint8_t imu;
        uint8_t gps;
    };

    class BITsResponse final : public Response
    {
    public:
        BITsResponse(const BitsInformation& bits);
        ~BITsResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        const BitsInformation& getBits() const;
        void setBITs(const BitsInformation& bits);

    private:
        virtual void initializeDataSize() override;

        BitsInformation bits_;
    };
}

#endif //AHRS_BITSRESPONSE_H
