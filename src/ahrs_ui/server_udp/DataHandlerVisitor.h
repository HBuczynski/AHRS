#ifndef AHRS_DATAHANDLERVISITOR_H
#define AHRS_DATAHANDLERVISITOR_H

#include <protocol/MeasuringDataVisitor.h>
#include <logger/Logger.h>

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
        utility::Logger& logger_;

    };
}
#endif
