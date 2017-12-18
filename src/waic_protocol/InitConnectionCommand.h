#ifndef AHRS_BLACK_BOX_WAIC_INIT_CONNECTION_COMMAND_H
#define AHRS_BLACK_BOX_WAIC_INIT_CONNECTION_COMMAND_H

#include "Command.h"
#include <string>

namespace communication
{
    class InitConnectionCommand final : public Command
    {
    public:
        InitConnectionCommand(uint16_t port, std::string address);
        ~InitConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

        uint16_t getPort();
        std::string getAddress();

    private:
        uint16_t serverListenUDPPort_;
        std::string serverAddress_;


    };
}

#endif