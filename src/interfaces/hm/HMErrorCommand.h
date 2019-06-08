#ifndef HMERRORCOMMAND_H
#define HMERRORCOMMAND_H

#include "HMCommand.h"
#include <common/HMNodes.h>

namespace communication
{
    class HMErrorCommand final : public HMCommand
    {
    public:
        HMErrorCommand(HMNodes node, HMErrorType error);
        ~HMErrorCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(HMCommandVisitor& visitor) override;

        HMNodes getHMNode() const;
        void setHMNode(HMNodes node);

        HMErrorType getHMError() const;
        void setHMError(HMErrorType error);

    private:
        virtual void initializeDataSize() override;

        HMNodes node_;
        HMErrorType error_;
    };
}

#endif // HMERRORCOMMAND_H
