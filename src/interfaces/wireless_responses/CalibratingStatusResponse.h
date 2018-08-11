#ifndef AHRS_CALIBRATINGSTATUSRESPONSE_H
#define AHRS_CALIBRATINGSTATUSRESPONSE_H

#include "Response.h"

namespace communication
{
    enum CalibrationStatus : uint8_t
    {
        PASSED = 0x01,
        FAILED = 0x02,
        IN_THE_PROCESS = 0x03
    };

    class CalibratingStatusResponse final : public Response
    {
    public:
        CalibratingStatusResponse(CalibrationStatus status);
        ~CalibratingStatusResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        CalibrationStatus getCalibrationStatus() const;
        void setCalibrationStatus(CalibrationStatus status);

    private:
        virtual void initializeDataSize() override;

        CalibrationStatus status_;
    };
}

#endif
