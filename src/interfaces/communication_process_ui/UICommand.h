#ifndef AHRS_UICOMMAND_H
#define AHRS_UICOMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class UICommandVisitor;

    enum UICommandType : uint8_t
    {
        CHANGE_STATE = 0x01,
        SHUTDOWN = 0x02,
        RECONNECT = 0x03,
        SEND_FRAME = 0x04,
        DATABASE_HASH = 0x05
    };

    class UICommand : public Frame
    {
    public:
        UICommand(uint8_t dataSizeIn, UICommandType commandTypeIn);
        virtual ~UICommand();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(UICommandVisitor& visitor) = 0;

        const UICommandType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        UICommandType commandType_;

    };
}

#endif
