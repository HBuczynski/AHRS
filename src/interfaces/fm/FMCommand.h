#ifndef FMCommand_H
#define FMCommand_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class FMCommandVisitor;

    enum FMCommandType : uint8_t
    {
        RESET_COMMUNICATION_PROCESS = 0x03,
        RESTART_MASTER_WITH_CHANGE = 0x06,
        CHANGE_CHANNEL = 0x08,
    };

    class FMCommand : public Frame
    {
    public:
        FMCommand(uint8_t dataSizeIn, FMCommandType notificationTypeIn);
        virtual ~FMCommand();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(FMCommandVisitor& visitor) = 0;

        const FMCommandType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        FMCommandType commandType_;
    };
}



#endif // FMCommand_H
