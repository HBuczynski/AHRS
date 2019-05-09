#ifndef DATABASEHASHCOMMAND_H
#define DATABASEHASHCOMMAND_H

#include "UICommand.h"
#include <string>

namespace communication
{
    class DatabaseHashCommand : public UICommand
    {
    public:
        DatabaseHashCommand(uint32_t hash, const std::string& name);
        ~DatabaseHashCommand();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UICommandVisitor& visitor) override;

        const std::string& getDbName() const noexcept;
        void setName(const std::string& name);

        uint32_t getHash() const noexcept;
        void setHash(uint32_t hash);

    private:
        virtual void initializeDataSize() override;

        std::string name_;
        uint32_t hash_;
    };
}

#endif // DATABASEHASHCOMMAND_H
