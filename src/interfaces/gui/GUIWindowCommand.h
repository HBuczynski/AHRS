#ifndef AHRS_GUIWINDOWCOMMAND_H
#define AHRS_GUIWINDOWCOMMAND_H

#include "GUICommand.h"

namespace communication
{
    enum class WindowType : uint8_t
    {
        CONNECTION_ESTABLISHED = 0x01,
        INFO_MASTER_OK = 0x02,
        INFO_MASTER_FALSE = 0x03,
        INFO_REDUNDANT_OK = 0x04,
        INFO_REDUNDANT_FALSE = 0x05,
        INFO_BITS_OK = 0x06,
        INFO_BITS_FALSE = 0x07,
        CHOOSING_PLANE = 0x08,
        CALIBRATION = 0x09,
        AHRS = 0x0A,
        RESTART = 0x0B,
        SHUTDOWN = 0x0C,
        WELCOME_PAGE = 0x11
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