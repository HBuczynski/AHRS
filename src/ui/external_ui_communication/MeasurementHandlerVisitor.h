#ifndef AHRS_DATAHANDLERVISITOR_H
#define AHRS_DATAHANDLERVISITOR_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
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
        void saveDataToSharedMemory(const std::vector<uint8_t> &rawData);

        config::UISharedMemory uiSharedMemoryParameters_;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

        utility::Logger& logger_;
    };
}
#endif
