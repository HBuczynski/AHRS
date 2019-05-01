#ifndef CALIBRATEDATABUILDER_H
#define CALIBRATEDATABUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class CalibrateDataBuilder final : public CommandBuilder
    {
    public:
        CalibrateDataBuilder();
        ~CalibrateDataBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}


#endif // CALIBRATEDATABUILDER_H
