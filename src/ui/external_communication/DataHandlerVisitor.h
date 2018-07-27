#ifndef AHRS_DATAHANDLERVISITOR_H
#define AHRS_DATAHANDLERVISITOR_H

#include "../../../../../../../../usr/include/boost/interprocess/shared_memory_object.hpp"
#include "../../../../../../../../usr/include/boost/interprocess/mapped_region.hpp"
#include "../../../../../../../../usr/include/boost/interprocess/sync/named_mutex.hpp"

#include "../../interfaces/wireless_measurement_commands/MeasuringDataVisitor.h"
#include "../../logger/Logger.h"

namespace communication
{
    class DataHandlerVisitor final : public MeasuringDataVisitor
    {
    public:
        DataHandlerVisitor();
        ~DataHandlerVisitor();

        virtual void visit(ImuData& data) override;
        virtual void visit(GpsData& data) override;

    private:
        void initializeSharedMemory();
        void saveDataToSharedMemory(const std::vector<uint8_t> &rawData);

        utility::Logger& logger_;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;
    };
}
#endif
