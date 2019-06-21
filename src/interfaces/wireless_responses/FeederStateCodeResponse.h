#ifndef AHRS_FeederStateCodeResponse_H
#define AHRS_FeederStateCodeResponse_H

#include "Response.h"
#include <common/FeederStates.h>

namespace communication
{
    class FeederStateCodeResponse final : public Response
    {
    public:
        FeederStateCodeResponse(FeederStateCode code);
        ~FeederStateCodeResponse();

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
