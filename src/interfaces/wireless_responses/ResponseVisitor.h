#ifndef AHRS_RESPONSEVISITOR_H
#define AHRS_RESPONSEVISITOR_H

#include "AckResponse.h"
#include "DataResponse.h"
#include "PlanesDatasetResponse.h"
#include "CalibratingStatusResponse.h"
#include "FeederStateCodeResponse.h"
#include "BITsResponse.h"
#include "CalibrateAccelerometerResponse.h"

namespace communication
{
    class ResponseVisitor
    {
    public:
        ResponseVisitor() {};
        virtual ~ResponseVisitor() {};

        virtual void visit(AckResponse& data) = 0;
        virtual void visit(DataResponse& data) = 0;
        virtual void visit(CalibratingStatusResponse& data) = 0;
        virtual void visit(PlanesDatasetResponse& data) = 0;
        virtual void visit(FeederStateCodeResponse& data) = 0;
        virtual void visit(BITsResponse& data) = 0;
        virtual void visit(CalibrateAccelerometerResponse& data) = 0;
    };
}

#endif //AHRS_RESPONSEVISITOR_H
