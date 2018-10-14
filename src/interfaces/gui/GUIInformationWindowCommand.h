#ifndef AHRS_GUIINFORMATIONWINDOWCOMMAND_H
#define AHRS_GUIINFORMATIONWINDOWCOMMAND_H

#include "GUICommand.h"

namespace communication
{
    class GUIInformationWindowCommand : public GUICommand
    {
    public:
        GUIInformationWindowCommand(uint8_t masterConnection, uint8_t redundantConnection, uint8_t bitsMaster, uint8_t bitsRedundant);
        ~GUIInformationWindowCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUICommandVisitor& visitor) override;

        void setMasterConnection(uint8_t state);
        uint8_t getMasterConnection() const;

        void setRedundantConnection(uint8_t state);
        uint8_t getRedundantConnection() const;

        void setBitsMaster(uint8_t state);
        uint8_t getBitsMaster() const;

        void setBitsRedundant(uint8_t state);
        uint8_t getBitsRedundant() const;

    private:
        virtual void initializeDataSize() override;

        uint8_t masterConnection_;
        uint8_t redundantConnection_;
        uint8_t bitsMaster_;
        uint8_t bitsRedundant_;
    };
}

#endif