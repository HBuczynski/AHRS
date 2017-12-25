#ifndef AHRS_ACKRESPONSE_H
#define AHRS_ACKRESPONSE_H

#include "Response.h"

namespace communication
{
    enum AckType : uint8_t
    {
        OK,
        FAIL
    };

    class AckResponse final : public Response
    {
    public:
        AckResponse(AckType type);
        ~AckResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

        AckType getAckType() const;
        void setAckType(AckType type);

    private:
        AckType type_;

    };
}

#endif //AHRS_ACKRESPONSE_H
