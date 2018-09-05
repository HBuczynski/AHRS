#ifndef AHRS_GUIWINDOWCOMMAND_H
#define AHRS_GUIWINDOWCOMMAND_H

#include "GUICommand.h"

namespace communication
{
    enum class WindowType : uint8_t
    {
        START_UP = 0x01,
        ACTIVE_CONNECTION = 0x02,
        CHOOSING_PLANE = 0x03,
        CALIBRATION = 0x04,
        AHRS = 0x05,
        RESTART = 0x06,
        SHUTDOWN = 0x07
    };

    class GUIWindowCommand : public GUICommand
    {
    public:
        GUIWindowCommand(WindowType windowType);
        ~GUIWindowCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUICommandVisitor& visitor) override;

        WindowType getWindowType() const;
        void setWindowType(WindowType windowType);

    private:
        virtual void initializeDataSize() override;

        WindowType windowType_;
    };
}

#endif