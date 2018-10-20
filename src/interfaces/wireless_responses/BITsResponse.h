#ifndef AHRS_BITSRESPONSE_H
#define AHRS_BITSRESPONSE_H

#include "Response.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class BITsResponse final : public Response
    {
    public:
        BITsResponse(uint8_t state, config::UICommunicationMode systemMode);
        ~BITsResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        uint8_t getState() const;
        void setState(uint8_t state);

        config::UICommunicationMode getSystemMode() const;
        void setSystemMode(config::UICommunicationMode systemMode);

    private:
        virtual void initializeDataSize() override;

        uint8_t state_;
        config::UICommunicationMode systemMode_;
    };
}

#endif //AHRS_BITSRESPONSE_H
