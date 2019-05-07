#ifndef STOPACQBUILDER_H
#define STOPACQBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class StopAcqBuilder final : public CommandBuilder
    {
    public:
        StopAcqBuilder();
        ~StopAcqBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // STOPACQBUILDER_H
