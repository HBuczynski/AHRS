#include "InterprocessExtCommunicationVisitor.h"

using namespace std;
using namespace utility;
using namespace communication;

InterprocessExtCommunicationVisitor::InterprocessExtCommunicationVisitor()
    : logger_(Logger::getInstance())
{}

InterprocessExtCommunicationVisitor::~InterprocessExtCommunicationVisitor()
{}

void InterprocessExtCommunicationVisitor::visit(const CalibrateMgnDemandCommand &command)
{

}

void InterprocessExtCommunicationVisitor::visit(const CalibrationStatusNotification& notification)
{

}

void InterprocessExtCommunicationVisitor::visit(const StateNotification &notification)
{
//    const auto status = command.getCalibrationStatus();

//    switch (status)
//    {
//        case CalibrationStatus::IN_THE_PROCESS :
//            clientUDPManager_->setNewState( new CalibratingState);
//            break;
//        case CalibrationStatus::FAILED :
//            clientUDPManager_->setNewState( new CalibratedFailedState);
//            break;
//        case CalibrationStatus::PASSED :
//            clientUDPManager_->setNewState( new CalibratedSuccessState);
//            break;
//        default:
//            if(logger_.isErrorEnable())
//            {
//                const string message = "InterprocessExtCommunicationVisitor: Inappropriate calibration state.";
//                logger_.writeLog(LogType::ERROR_LOG, message);
//            }
//            break;
//    }
}

void InterprocessExtCommunicationVisitor::initializeClientUDPManager(std::shared_ptr<ClientUDPManager> clientUDPManager)
{
    clientUDPManager_ = clientUDPManager;
}
