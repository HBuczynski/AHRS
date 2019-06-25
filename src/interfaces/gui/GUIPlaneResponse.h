#ifndef AHRS_GUIPLANERESPONSE_H
#define AHRS_GUIPLANERESPONSE_H

#include "GUIResponse.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class GUIPlaneResponse final : public GUIResponse
    {
    public:
        GUIPlaneResponse(config::UICommunicationMode mode, const std::string& plane);
        ~GUIPlaneResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

        const std::string& getPlane() const;
        void setPlane(const std::string& plane);

        config::UICommunicationMode getMode() const;
        void setMode(const config::UICommunicationMode &mode);

    private:
        virtual void initializeDataSize() override;

        config::UICommunicationMode mode_;
        std::string plane_;
    };
}

#endif
