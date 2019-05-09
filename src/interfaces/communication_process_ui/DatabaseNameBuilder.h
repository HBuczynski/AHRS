#ifndef DATABASENAMEBUILDER_H
#define DATABASENAMEBUILDER_H

#include <UINotificationBuilder.h>

namespace communication
{
    class DatabaseNameBuilder final : public UINotificationBuilder
    {
    public:
        DatabaseNameBuilder();
        ~DatabaseNameBuilder();

        std::unique_ptr<UINotification> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // DATABASENAMEBUILDER_H
