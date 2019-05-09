#ifndef DBHASHBUILDER_H
#define DBHASHBUILDER_H

#include "FeederNotificationBuilder.h"

namespace communication
{
    class DbHashBuilder final : public FeederNotificationBuilder
    {
    public:
        DbHashBuilder();
        ~DbHashBuilder();

        virtual std::unique_ptr<FeederNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // DBHASHBUILDER_H
