#ifndef AHRS_HMErrorNotification_H
#define AHRS_HMErrorNotification_H

#include "HMNotification.h"
#include <common/HMNodes.h>
#include <config_reader/UIParameters.h>

namespace communication
{
    class HMErrorNotification final : public HMNotification
    {
    public:
        HMErrorNotification(HMNodes node, HMErrorType error, config::UICommunicationMode mode);
        ~HMErrorNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(HMNotificationVisitor& visitor) override;

        HMNodes getHMNode() const;
        void setHMNode(HMNodes node);

        HMErrorType getHMError() const;
        void setHMError(HMErrorType error);

        config::UICommunicationMode getMode() const;
        void setMode(const config::UICommunicationMode &mode);

    private:
        virtual void initializeDataSize() override;

        HMNodes node_;
        HMErrorType error_;
        config::UICommunicationMode mode_;
    };
}


#endif
