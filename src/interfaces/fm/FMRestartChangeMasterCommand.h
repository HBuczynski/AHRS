#ifndef HMRESTARTCHANGEMASTERCOMMAND_H
#define HMRESTARTCHANGEMASTERCOMMAND_H

#include "FMCommand.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class FMRestartChangeMasterCommand final : public FMCommand
    {
    public:
        FMRestartChangeMasterCommand();
        ~FMRestartChangeMasterCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FMCommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;

    };
}


#endif // HMRESTARTCHANGEMASTERCOMMAND_H
