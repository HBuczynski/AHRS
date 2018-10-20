#ifndef AHRS_RESPONSEHANDLERVISITOR_H
#define AHRS_RESPONSEHANDLERVISITOR_H

#include <interfaces/wireless_responses/ResponseVisitor.h>
#include <logger/Logger.h>
#include <boost/interprocess/ipc/message_queue.hpp>

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
        virtual void visit(PlanesDatasetResponse& data) override;
        virtual void visit(CurrentStateResponse& data) override ;
        virtual void visit(BITsResponse& data) override;

    private:
        void initializeMessageQueue();

        void sendMessage(std::vector<uint8_t> msg);

        config::UIMessageQueues uiMessageQueuesParameters_;
        std::unique_ptr<boost::interprocess::message_queue> sendingMessageQueue_;

        utility::Logger& logger_;
    };
}

#endif