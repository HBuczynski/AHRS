#ifndef AHRS_PLANESDATASETRESPONSE_H
#define AHRS_PLANESDATASETRESPONSE_H

#include "Response.h"
#include <config_reader/AircraftParameters.h>

#include <string>
#include <vector>

namespace communication
{
    class PlanesDatasetResponse final : public Response
    {
    public:
        PlanesDatasetResponse(const std::vector<config::AircraftParameters> &dataset);
        ~PlanesDatasetResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        void setDataset(const std::vector<config::AircraftParameters> &dataset);

        const std::vector<config::AircraftParameters>& getDataset() const;

    private:
        virtual void initializeDataSize() override;

        std::vector<config::AircraftParameters> dataset_;
    };
}

#endif