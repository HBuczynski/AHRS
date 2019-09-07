#ifndef AHRS_GUIRESPONSE_H
#define AHRS_GUIRESPONSE_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class GUIResponseVisitor;

    enum GUIResponseType : uint8_t
    {
        SET_PLANE = 0x01,
        WINDOWS_TYPE = 0x02,
        WRAPPER = 0x03,
        GUI_START_ACQ = 0x04,
        GUI_STOP_ACQ = 0x05,
        GUI_SHUTDOWN = 0x07,
        GUI_RESTART = 0x08
    };

    class GUIResponse : public Frame
    {
    public:
        GUIResponse(uint8_t dataSizeIn, GUIResponseType commandTypeIn);
        virtual ~GUIResponse();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(GUIResponseVisitor& visitor) = 0;

        const GUIResponseType& getResponseType() const;

    protected:
        virtual void initializeDataSize() = 0;

        GUIResponseType responseType_;

    };
}

#endif
