#ifndef AHRS_DATAHANDLERVISITOR_H
#define AHRS_DATAHANDLERVISITOR_H

#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <config_reader/UIParameters.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataVisitor.h>

#include <vector>
#include <logger/Logger.h>

namespace communication
{
    class MeasurementHandlerVisitor final : public MeasuringDataVisitor
    {
    public:
        MeasurementHandlerVisitor();
        ~MeasurementHandlerVisitor();

        virtual void visit(ImuData& data) override;
        virtual void visit(GpsData& data) override;
        virtual void visit(FlightData& data) override;

    private:
        void initializeSharedMemory();
        void writeDataToSharedMemory(std::vector<uint8_t> &rawData);

        config::UISharedMemory uiSharedMemoryParameters_;

        std::unique_ptr<communication::SharedMemoryWrapper> sharedMemory_;

        utility::Logger& logger_;
    };
}
#endif
