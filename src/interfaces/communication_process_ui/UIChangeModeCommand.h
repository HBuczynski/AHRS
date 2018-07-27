#ifndef AHRS_UICHANGESTATECOMMAND_H
#define AHRS_UICHANGESTATECOMMAND_H

#include "UICommand.h"
#include <string>

namespace communication
{
    enum CommunicationProcessMode : uint8_t
    {
        MAIN,
        REDUNDANT,
    };

    class UIChangeModeCommand : public UICommand
    {
    public:
        UIChangeModeCommand(const CommunicationProcessMode &name);
        ~UIChangeModeCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UICommandVisitor& visitor) override;

        CommunicationProcessMode getMode() const;
        void setMode(CommunicationProcessMode mode);

    private:
        virtual void initializeDataSize() override;

        CommunicationProcessMode mode_;

    };
}
#endif //AHRS_UICHANGESTATECOMMAND_H
