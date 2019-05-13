#ifndef AHRS_DATAHANDLERVISITOR_H
#define AHRS_DATAHANDLERVISITOR_H

#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <config_reader/UIParameters.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataVisitor.h>

#include <vector>
#include <logger/Logger.h>
#include <database_manager/CockpitDb.h>

#include <thread>

namespace communication
{
    class CommunicationManagerUI;

    class MeasurementHandlerVisitor final : public MeasuringDataVisitor
    {
    public:
        MeasurementHandlerVisitor(CommunicationManagerUI* communicationManagerUI);
        ~MeasurementHandlerVisitor();

        virtual void visit(ImuData& data) override;
        virtual void visit(GpsData& data) override;
        virtual void visit(FeederData& data) override;
        virtual void visit(UDPBitsData& data) override;

        void initializeDB(uint32_t hash, const std::string& name);

    private:
        void initializeSharedMemory();
        void writeDataToSharedMemory(std::vector<uint8_t> &rawData);
        void trolo();

        CommunicationManagerUI* communicationManagerUI_;
        config::UISharedMemory uiSharedMemoryParameters_;

        std::shared_ptr<database::CockpitDb> cockpitDb_;
        std::unique_ptr<communication::SharedMemoryWrapper> sharedMemory_;

        utility::Logger& logger_;
    };
}
#endif
