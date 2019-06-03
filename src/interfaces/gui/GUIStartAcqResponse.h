#ifndef GUISTARTACQRESPONSE_H
#define GUISTARTACQRESPONSE_H

#include "GUIResponse.h"

namespace communication
{
    class GUIStartAcqResponse final : public GUIResponse
    {
    public:
        GUIStartAcqResponse();
        ~GUIStartAcqResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // GUISTARTACQRESPONSE_H
