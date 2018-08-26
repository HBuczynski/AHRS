#ifndef AHRS_RECONNECTCOMMAND_H
#define AHRS_RECONNECTCOMMAND_H

#include "UICommand.h"

namespace communication
{
    class ReconnectCommand : public UICommand
    {
    public:
        ReconnectCommand();
        ~ReconnectCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UICommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif