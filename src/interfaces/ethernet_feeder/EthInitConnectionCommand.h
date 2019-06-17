#ifndef ETHINITCONNECTIONCOMMAND_H
#define ETHINITCONNECTIONCOMMAND_H

#include "EthFeederCommand.h"

namespace communication
{
    class EthInitConnectionCommand : public EthFeederCommand
    {
    public:
        EthInitConnectionCommand(uint16_t port, std::string address);
        ~EthInitConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederCommandVisitor& visitor) override;

        uint16_t getServerListenUDPPort() const;
        void setServerListenUDPPort(const uint16_t &serverListenUDPPort);

        std::string getServerAddress() const;
        void setServerAddress(const std::string &serverAddress);

    private:
        virtual void initializeDataSize() override;

        uint16_t serverListenUDPPort_;
        std::string serverAddress_;
    };
}


#endif // ETHINITCONNECTIONCOMMAND_H
