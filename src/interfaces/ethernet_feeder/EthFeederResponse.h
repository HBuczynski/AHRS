#ifndef ETHFEEDERRESPONSE_H
#define ETHFEEDERRESPONSE_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class EthFeederResponseVisitor;

    enum EthResponseType : uint8_t
    {

    };

    class EthFeederResponse : public Frame
    {
    public:
        EthFeederResponse(uint8_t dataSizeIn, EthResponseType commandTypeIn);
        virtual ~EthFeederResponse();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(EthFeederResponseVisitor& visitor) = 0;

        const EthResponseType& getResponseType() const;

    protected:
        virtual void initializeDataSize() = 0;

        EthResponseType responseType_;

    };
}

#endif // ETHFEEDERRESPONSE_H
