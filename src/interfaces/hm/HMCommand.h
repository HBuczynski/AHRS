#ifndef HMCOMMAND_H
#define HMCOMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class HMCommandVisitor;

    enum HMCommandType : uint8_t
    {
        COMMAND_ERROR = 0x03,
    };

    class HMCommand : public Frame
    {
    public:
        HMCommand(uint8_t dataSizeIn, HMCommandType notificationTypeIn);
        virtual ~HMCommand();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(HMCommandVisitor& visitor) = 0;

        const HMCommandType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        HMCommandType commandType_;
    };
}



#endif // HMCOMMAND_H
