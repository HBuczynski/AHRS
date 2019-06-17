#ifndef AHRS_ETHFEEDERCOMMAND_H
#define AHRS_ETHFEEDERCOMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class EthFeederCommandVisitor;

    enum EthCommandType : uint8_t
    {
        ETH_INIT_CONNECTION = 10,
        ETH_HANDSHAKE = 15,
        ETH_CHANGE_STATE = 20,
    };

    class EthFeederCommand : public Frame
    {
    public:
        EthFeederCommand(uint8_t dataSizeIn, EthCommandType ethCommandTypeIn);
        virtual ~EthFeederCommand();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(EthFeederCommandVisitor& visitor) = 0;

        const EthCommandType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        EthCommandType commandType_;
    };
}

#endif
