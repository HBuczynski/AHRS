#ifndef AHRS_GUIBITSCOMMAND_H
#define AHRS_GUIBITSCOMMAND_H

#include "GUICommand.h"
#include <interfaces/wireless_responses/BITsResponse.h>

namespace communication
{
    class GUIBITSCommand : public GUICommand
    {
    public:
        GUIBITSCommand(const BitsInformation& bitsInformation);
        ~GUIBITSCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUICommandVisitor& visitor) override;

        void setBitsInfo(const BitsInformation& info) noexcept;
        const BitsInformation& getBitsInfo() const noexcept;

    private:
        virtual void initializeDataSize() override;

        BitsInformation bitsInfo_;
    };
}

#endif
