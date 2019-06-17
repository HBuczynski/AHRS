#ifndef ETHACKFEEDERRESPONSE_H
#define ETHACKFEEDERRESPONSE_H

#include "EthFeederResponse.h"
#include <common/FeederStates.h>

namespace communication
{
    class EthAckFeederResponse : public EthFeederResponse
    {
    public:
        EthAckFeederResponse();
        ~EthAckFeederResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(EthFeederResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}


#endif // ETHACKFEEDERRESPONSE_H
