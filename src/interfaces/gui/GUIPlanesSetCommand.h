#ifndef AHRS_GUIPLANESETCommand_H
#define AHRS_GUIPLANESETCommand_H

#include "GUICommand.h"

#include <string>
#include <vector>

namespace communication
{
    class GUIPlanesSetCommand final : public GUICommand
    {
    public:
        GUIPlanesSetCommand(const std::string& dataset);
        ~GUIPlanesSetCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUICommandVisitor& visitor) override;

        void setDataset(const std::string& dataset);

        std::string getDataset() const;

    private:
        virtual void initializeDataSize() override;

        std::string dataset_;
    };
}

#endif
