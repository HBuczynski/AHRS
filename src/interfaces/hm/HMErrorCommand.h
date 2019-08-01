#ifndef HMERRORCOMMAND_H
#define HMERRORCOMMAND_H

#include "HMCommand.h"
#include <common/HMNodes.h>
#include <config_reader/UIParameters.h>

namespace communication
{
    class HMErrorCommand final : public HMCommand
    {
    public:
        HMErrorCommand(HMNodes node, HMErrorType error, config::UICommunicationMode mode, const std::string& systemState);
        ~HMErrorCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(HMCommandVisitor& visitor) override;

        HMNodes getHMNode() const;
        void setHMNode(HMNodes node);

        HMErrorType getHMError() const;
        void setHMError(HMErrorType error);

        config::UICommunicationMode getMode() const;
        void setMode(const config::UICommunicationMode &mode);

        std::string getSystemState() const;
        void setSystemState(const std::string &systemState);

    private:
        virtual void initializeDataSize() override;

        HMNodes node_;
        HMErrorType error_;
        config::UICommunicationMode mode_;
        std::string systemState_;
    };
}

#endif // HMERRORCOMMAND_H
