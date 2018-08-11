#ifndef AHRS_RESPONSEHANDLERVISITOR_H
#define AHRS_RESPONSEHANDLERVISITOR_H

#include <interfaces/wireless_responses/ResponseVisitor.h>
#include <logger/Logger.h>

namespace communication
{
    class ResponseHandlerVisitor final : public ResponseVisitor
    {
    public:
        ResponseHandlerVisitor();
        ~ResponseHandlerVisitor();

        virtual void visit(AckResponse& data) override;
        virtual void visit(DataResponse& data) override;
        virtual void visit(CalibratingStatusResponse& data) override;

    private:
        utility::Logger& logger_;
    };
}

#endif