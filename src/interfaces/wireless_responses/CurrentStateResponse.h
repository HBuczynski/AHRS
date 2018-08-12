#ifndef AHRS_CURRENTSTATERESPONSE_H
#define AHRS_CURRENTSTATERESPONSE_H

#include "Response.h"
#include <system_states/FeederExternalComStates.h>

namespace communication
{
    class CurrentStateResponse final : public Response
    {
    public:
        CurrentStateResponse(StateCode code);
        ~CurrentStateResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        StateCode getStateCode() const;
        void setAckType(StateCode code);

    private:
        virtual void initializeDataSize() override;

        StateCode code_;
    };
}


#endif