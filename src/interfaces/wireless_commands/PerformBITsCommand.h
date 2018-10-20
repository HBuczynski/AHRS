#ifndef AHRS_PERFORMBITSCOMMAND_H
#define AHRS_PERFORMBITSCOMMAND_H

#include "Command.h"
#include <string>

namespace communication
{
    class PerformBITsCommand final : public Command
    {
    public:
        PerformBITsCommand();
        ~PerformBITsCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif //AHRS_PERFORMBITSCOMMAND_H
