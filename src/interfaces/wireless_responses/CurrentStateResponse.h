#ifndef AHRS_CURRENTSTATERESPONSE_H
#define AHRS_CURRENTSTATERESPONSE_H

#include "Response.h"
#include <common/FeederStates.h>

namespace communication
{
    class CurrentStateResponse final : public Response
    {
    public:
        CurrentStateResponse(FeederStateCode code);
        ~CurrentStateResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        FeederStateCode getStateCode() const;
        void setAckType(FeederStateCode code);

    private:
        virtual void initializeDataSize() override;

        FeederStateCode code_;
    };
}


#endif