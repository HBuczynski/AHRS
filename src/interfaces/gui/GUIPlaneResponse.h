#ifndef AHRS_GUIPLANERESPONSE_H
#define AHRS_GUIPLANERESPONSE_H

#include "GUIResponse.h"

namespace communication
{
    class GUIPlaneResponse final : public GUIResponse
    {
    public:
        GUIPlaneResponse(const std::string& plane);
        ~GUIPlaneResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

        const std::string& getPlane() const;
        void setPlane(const std::string& plane);

    private:
        virtual void initializeDataSize() override;

        std::string plane_;
    };
}

#endif