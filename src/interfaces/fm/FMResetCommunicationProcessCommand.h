#ifndef FMRESETCOMMUNICATIONPROCESSCOMMAND_H
#define FMRESETCOMMUNICATIONPROCESSCOMMAND_H

#include "FMCommand.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class FMResetCommunicationProcessCommand final : public FMCommand
    {
    public:
        FMResetCommunicationProcessCommand(config::UICommunicationMode mode);
        ~FMResetCommunicationProcessCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FMCommandVisitor& visitor) override;

        config::UICommunicationMode getMode() const;
        void setMode(const config::UICommunicationMode &mode);

    private:
        virtual void initializeDataSize() override;

        config::UICommunicationMode mode_;
    };
}

#endif // FMRESESCOMMUNICATIONPROCESSCOMMAND_H
