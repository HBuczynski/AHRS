#ifndef AHRS_PLANESDATASETBUILDER_H
#define AHRS_PLANESDATASETBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class PlanesDatasetBuilder final : public ResponseBuilder
    {
    public:
        PlanesDatasetBuilder();
        ~PlanesDatasetBuilder();

        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif
