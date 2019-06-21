#ifndef FEEDERCODEDEMANDBUILDER_H
#define FEEDERCODEDEMANDBUILDER_H

#include "FeederCommandBuilder.h"

namespace communication
{
    class FeederCodeDemandBuilder final : public FeederCommandBuilder
    {
    public:
        FeederCodeDemandBuilder();
        ~FeederCodeDemandBuilder();

        virtual std::unique_ptr<FeederCommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // FEEDERCODEDEMANDBUILDER_H
