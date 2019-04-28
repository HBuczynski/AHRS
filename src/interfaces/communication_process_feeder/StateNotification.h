#ifndef AHRS_StateNotification_H
#define AHRS_StateNotification_H

#include "FeederNotification.h"
#include <common/FeederStates.h>

namespace communication
{
    class StateNotification final : public FeederNotification
    {
    public:
        StateNotification(FeederStateCode code);
        ~StateNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FeederNotificationVisitor& visitor) override;

        FeederStateCode getStateCode() const;
        void setAckType(FeederStateCode code);

    private:
        virtual void initializeDataSize() override;

        FeederStateCode code_;
    };
}


#endif
