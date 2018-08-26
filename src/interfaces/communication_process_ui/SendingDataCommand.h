#ifndef AHRS_SENDINGDATACOMMAND_H
#define AHRS_SENDINGDATACOMMAND_H

#include "UICommand.h"

namespace communication
{
    class SendingDataCommand : public UICommand
    {
    public:
        SendingDataCommand(const std::vector<uint8_t> &data);
        ~SendingDataCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UICommandVisitor& visitor) override;

        const std::vector<uint8_t>& getDataFrame() const;
        void setDataFrame(const std::vector<uint8_t>& data);
    private:
        virtual void initializeDataSize() override;

        std::vector<uint8_t> data_;
    };
}

#endif