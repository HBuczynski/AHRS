#ifndef AHRS_GUIWINDOWCOMMAND_H
#define AHRS_GUIWINDOWCOMMAND_H

#include "GUICommand.h"
#include <../../common/UIStates.h>

namespace communication
{
    class GUIWindowCommand : public GUICommand
    {
    public:
        GUIWindowCommand(PagesType windowType);
        ~GUIWindowCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUICommandVisitor& visitor) override;

        PagesType getWindowType() const;
        void setWindowType(PagesType windowType);

    private:
        virtual void initializeDataSize() override;

        PagesType windowType_;
    };
}

#endif