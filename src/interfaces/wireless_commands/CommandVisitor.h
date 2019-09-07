#ifndef AHRS_BLACK_BOX_FRAMEVISITOR_H
#define AHRS_BLACK_BOX_FRAMEVISITOR_H

#include "InitConnectionCommand.h"
#include "EndConnectionCommand.h"
#include "CallibrateMagnetometerCommand.h"
#include "CollectDataCommand.h"
#include "SetPlaneCommand.h"
#include "RemovePlaneDataCommand.h"
#include "CalibrationStatusCommand.h"
#include "StartAcquisitionCommand.h"
#include "CurrentStateCommand.h"
#include "PerformBITsCommand.h"
#include "CalibrateAccelerometerCommand.h"
#include "CalibrateDataCommand.h"
#include "BITSDataCommand.h"
#include "StopAcqCommand.h"
#include "SetHashCommand.h"
#include "UDPBitsCommand.h"
#include "HandshakeCommand.h"
#include "ChangeStateCommand.h"
#include "KeepAliveCommand.h"
#include "ChangeFeederModeCommand.h"
#include "RestartCommand.h"
#include "ShutdownCommand.h"

namespace communication
{
    class CommandVisitor
    {
    public:
        CommandVisitor(){};
        virtual ~CommandVisitor(){};

        virtual void visit(InitConnectionCommand& command) = 0;
        virtual void visit(EndConnectionCommand& command) = 0;
        virtual void visit(CallibrateMagnetometerCommand& command) = 0;
        virtual void visit(CollectDataCommand& command) = 0;
        virtual void visit(SetPlaneCommand& command) = 0;
        virtual void visit(RemovePlaneDataCommand& command) = 0;
        virtual void visit(CalibrationStatusCommand& command) = 0;
        virtual void visit(StartAcquisitionCommand& command) = 0;
        virtual void visit(CurrentStateCommand& command) = 0;
        virtual void visit(PerformBITsCommand& command) = 0;
        virtual void visit(CalibrateAccelerometerCommand& command) = 0;
        virtual void visit(CalibrateDataCommand& command) = 0;
        virtual void visit(BITSDataCommand& command) = 0;
        virtual void visit(StopAcqCommand& command) = 0;
        virtual void visit(SetHashCommand& command) = 0;
        virtual void visit(UDPBitsCommand& command) = 0;
        virtual void visit(HandshakeCommand& command) = 0;
        virtual void visit(ChangeStateCommand& command) = 0;
        virtual void visit(KeepAliveCommand& command) = 0;
        virtual void visit(ChangeFeederModeCommand& command) = 0;
        virtual void visit(RestartCommand& command) = 0;
        virtual void visit(ShutdownCommand& command) = 0;
    };
}
#endif
