#ifndef DATABASEHASHBUILDER_H
#define DATABASEHASHBUILDER_H

#include "UICommandBuilder.h"

namespace communication
{
    class DatabaseHashBuilder final : public UICommandBuilder
    {
    public:
        DatabaseHashBuilder();
        ~DatabaseHashBuilder();

        std::unique_ptr<UICommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // DATABASEHASHBUILDER_H
