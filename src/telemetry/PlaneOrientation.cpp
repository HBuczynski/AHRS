#include "PlaneOrientation.h"

using namespace std;
using namespace utility;
using namespace telemetry;

PlaneOrientation::PlaneOrientation()
    : lsm9DS1Driver_(IMU_MODE_I2C, 0x6b, 0x1e),
      logger_(Logger::getInstance())
{}

PlaneOrientation::~PlaneOrientation()
{}

void PlaneOrientation::initDataAcquisition()
{
    if (!lsm9DS1Driver_.begin())
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("PlaneOrientation :: lsm9DS1Driver_ cannot  begin acq.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    mahony_.begin(10);
}

void PlaneOrientation::readData()
{
    while (!lsm9DS1Driver_.gyroAvailable()) ;
    lsm9DS1Driver_.readGyro();
    while(!lsm9DS1Driver_.accelAvailable()) ;
    lsm9DS1Driver_.readAccel();
    while(!lsm9DS1Driver_.magAvailable()) ;
    lsm9DS1Driver_.readMag();

    mahony_.update(lsm9DS1Driver_.calcGyro(lsm9DS1Driver_.gx), lsm9DS1Driver_.calcGyro(lsm9DS1Driver_.gy), lsm9DS1Driver_.calcGyro(lsm9DS1Driver_.gz),
                     lsm9DS1Driver_.calcAccel(lsm9DS1Driver_.ax), lsm9DS1Driver_.calcAccel(lsm9DS1Driver_.ay), lsm9DS1Driver_.calcAccel(lsm9DS1Driver_.az),
                     lsm9DS1Driver_.calcMag(lsm9DS1Driver_.mx), lsm9DS1Driver_.calcMag(lsm9DS1Driver_.my), lsm9DS1Driver_.calcMag(lsm9DS1Driver_.mz));
}

float PlaneOrientation::getPitch()
{
    return mahony_.getPitch();
}

float PlaneOrientation::getRoll()
{
    return mahony_.getRoll();
}

float PlaneOrientation::getYaw()
{
    return mahony_.getYaw();
}

