#ifndef AHRS_GUICOMMAND_H
#define AHRS_GUICOMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class GUICommandVisitor;

    enum GUICommandType : uint8_t
    {
        CHANGE_WINDOW = 0x01
    };

    class GUICommand : public Frame
    {
    public:
        GUICommand(uint8_t dataSizeIn, GUICommandType commandTypeIn);
        virtual ~GUICommand();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(GUICommandVisitor& visitor) = 0;

        const GUICommandType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        GUICommandType commandType_;
    };
}

#endif