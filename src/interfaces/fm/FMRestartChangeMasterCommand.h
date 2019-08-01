#ifndef HMRESTARTCHANGEMASTERCOMMAND_H
#define HMRESTARTCHANGEMASTERCOMMAND_H

#include "FMCommand.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class FMRestartChangeMasterCommand final : public FMCommand
    {
    public:
        FMRestartChangeMasterCommand(std::string systemState);
        ~FMRestartChangeMasterCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FMCommandVisitor& visitor) override;

        std::string getSystemState() const;
        void setSystemState(const std::string &systemState);

    private:
        virtual void initializeDataSize() override;

        std::string systemState_;
    };
}


#endif // HMRESTARTCHANGEMASTERCOMMAND_H
