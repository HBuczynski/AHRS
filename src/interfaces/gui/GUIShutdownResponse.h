#ifndef GUISHUTDOWNRESPONSE_H
#define GUISHUTDOWNRESPONSE_H

#include "GUIResponse.h"

namespace communication
{
    class GUIShutdownResponse final : public GUIResponse
    {
    public:
        GUIShutdownResponse();
        ~GUIShutdownResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif // GUISHUTDOWNRESPONSE_H
