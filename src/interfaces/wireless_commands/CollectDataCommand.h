#ifndef AHRS_COLLECTDATACOMMAND_H
#define AHRS_COLLECTDATACOMMAND_H

#include "Command.h"

namespace communication
{
    class CollectDataCommand : public Command
    {
    public:
        CollectDataCommand();
        ~CollectDataCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif
