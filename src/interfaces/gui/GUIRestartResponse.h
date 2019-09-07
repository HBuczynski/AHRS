#ifndef GUIRESTARTRESPONSE_H
#define GUIRESTARTRESPONSE_H

#include "GUIResponse.h"

namespace communication
{
    class GUIRestartResponse final : public GUIResponse
    {
    public:
        GUIRestartResponse();
        ~GUIRestartResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}


#endif // GUIRESTARTRESPONSE_H
