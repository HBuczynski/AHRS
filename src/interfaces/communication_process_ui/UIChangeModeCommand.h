#ifndef AHRS_UICHANGESTATECOMMAND_H
#define AHRS_UICHANGESTATECOMMAND_H

#include "UICommand.h"
#include <string>
#include <config_reader/UIParameters.h>

namespace communication
{
    class UIChangeModeCommand : public UICommand
    {
    public:
        UIChangeModeCommand(config::UICommunicationMode mode);
        ~UIChangeModeCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UICommandVisitor& visitor) override;

        config::UICommunicationMode getMode() const;
        void setMode(config::UICommunicationMode mode);

    private:
        virtual void initializeDataSize() override;

        config::UICommunicationMode mode_;
    };
}
#endif
