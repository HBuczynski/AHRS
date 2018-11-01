#ifndef AHRS_GUIWINDOWRESPONSE_H
#define AHRS_GUIWINDOWRESPONSE_H

#include "GUIResponse.h"
#include <../../system_states/UIStates.h>

namespace communication
{
    class GUIWindowResponse final : public GUIResponse
    {
    public:
        GUIWindowResponse(PagesType pageType);
        ~GUIWindowResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

        PagesType getPageType() const;
        void setPageType(PagesType pageType);

    private:
        virtual void initializeDataSize() override;

        PagesType pageType_;
    };
}

#endif