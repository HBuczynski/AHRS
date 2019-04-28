#ifndef CALIBRATEACCELEROMETERRESPONSE_H
#define CALIBRATEACCELEROMETERRESPONSE_H

#include "Response.h"
#include <vector>

namespace communication
{
    enum class AccelActionResponse : uint8_t
    {
        OK = 0x01,
        ERROR = 0x02,
        FINISH = 0x03
    };

    class CalibrateAccelerometerResponse final : public Response
    {
    public:
        CalibrateAccelerometerResponse(AccelActionResponse status);
        ~CalibrateAccelerometerResponse();

        virtual std::vector<uint8_t> getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(ResponseVisitor& visitor) override;

        void setActionResponse(AccelActionResponse status) noexcept;
        AccelActionResponse getActionResponse() const noexcept;

    private:
        virtual void initializeDataSize() override;

        AccelActionResponse status_;
    };
}


#endif // CALIBRATEACCELEROMETERRESPONSE_H
