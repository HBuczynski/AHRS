#ifndef AHRS_GUIINFORMATIONWINDOWCOMMAND_H
#define AHRS_GUIINFORMATIONWINDOWCOMMAND_H

#include "GUICommand.h"

namespace communication
{
    class GUIInformationWindowCommand : public GUICommand
    {
    public:
        GUIInformationWindowCommand(uint8_t masterConnection, uint8_t redundantConnection, uint8_t bitsPerformance);
        ~GUIInformationWindowCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUICommandVisitor& visitor) override;

        void setMasterConnection(uint8_t state);
        uint8_t getMasterConnection() const;

        void setRedundantConnection(uint8_t state);
        uint8_t getRedundantConnection() const;

        void setBitsPerformance(uint8_t state);
        uint8_t getBitsPerformance() const;

    private:
        virtual void initializeDataSize() override;

        uint8_t masterConnection_;
        uint8_t redundantConnection_;
        uint8_t bitsPerformance_;
    };
}

#endif