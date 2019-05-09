#ifndef DBHASHNOTIFICATION_H
#define DBHASHNOTIFICATION_H

#include "FeederNotification.h"

namespace communication
{
    class DbHashNotification final : public FeederNotification
    {
    public:
        DbHashNotification(uint32_t hash);
        ~DbHashNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FeederNotificationVisitor& visitor) override;

        uint32_t getHash() const noexcept;
        void setHash(uint32_t hash) noexcept;

    private:
        virtual void initializeDataSize() override;

        uint32_t hash_;
    };
}

#endif // DBHASHNOTIFICATION_H
