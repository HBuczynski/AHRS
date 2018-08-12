#ifndef AHRS_BLACK_BOX_WAICRESPONSE_H
#define AHRS_BLACK_BOX_WAICRESPONSE_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class ResponseVisitor;

    enum ResponseType : uint8_t
    {
        DATA = 10,
        ACK = 20,
        CALIBRATING_STATUS = 30,
        PLANES_DATASET = 40,
        CURRENT_STATE_RES = 50
    };

    class Response : public Frame
    {
    public:
        Response(uint8_t dataSizeIn, ResponseType commandTypeIn);
        virtual ~Response();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(ResponseVisitor& visitor) = 0;

        const ResponseType& getResponseType() const;

    protected:
        virtual void initializeDataSize() = 0;

        ResponseType responseType_;

    };
}

#endif
