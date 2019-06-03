#ifndef GUISTOPACQRESPONSE_H
#define GUISTOPACQRESPONSE_H

#include "GUIResponse.h"

namespace communication
{
    class GUIStopAcqResponse final : public GUIResponse
    {
    public:
        GUIStopAcqResponse();
        ~GUIStopAcqResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // GUISTOPACQRESPONSE_H
