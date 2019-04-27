#ifndef AHRS_CURRENTSTATEBUILDER_H
#define AHRS_CURRENTSTATEBUILDER_H

#include "FeederNotificationBuilder.h"

namespace communication
{
    class StateBuilder final : public FeederNotificationBuilder
    {
    public:
        StateBuilder();
        ~StateBuilder();

        virtual std::unique_ptr<FeederNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif
