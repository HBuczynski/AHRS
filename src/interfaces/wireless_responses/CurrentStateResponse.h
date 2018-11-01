#ifndef AHRS_CURRENTSTATERESPONSE_H
#define AHRS_CURRENTSTATERESPONSE_H

#include "Response.h"
#include <system_states/FeederStates.h>

namespace communication
{
    class CurrentStateResponse final : public Response
    {
    public:
        CurrentStateResponse(FeederExternalStateCode code);
        ~CurrentStateResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        FeederExternalStateCode getStateCode() const;
        void setAckType(FeederExternalStateCode code);

    private:
        virtual void initializeDataSize() override;

        FeederExternalStateCode code_;
    };
}


#endif