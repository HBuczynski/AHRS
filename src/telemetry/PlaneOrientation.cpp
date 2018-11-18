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

    mahony_.begin(200)
}

void PlaneOrientation::readData()
{
    while (!lsm9DS1Driver_.gyroAvailable()) ;
    lsm9DS1Driver_.readGyro();
    while(!lsm9DS1Driver_.accelAvailable()) ;
    lsm9DS1Driver_.readAccel();
    while(!lsm9DS1Driver_.magAvailable()) ;
    lsm9DS1Driver_.readMag();

    auto gx = lsm9DS1Driver_.calcGyro(lsm9DS1Driver_.gx);
    auto gy = lsm9DS1Driver_.calcGyro(lsm9DS1Driver_.gy);
    auto gz = lsm9DS1Driver_.calcGyro(lsm9DS1Driver_.gz);

    auto ax = lsm9DS1Driver_.calcAccel(lsm9DS1Driver_.ax);
    auto ay = lsm9DS1Driver_.calcAccel(lsm9DS1Driver_.ay);
    auto az = lsm9DS1Driver_.calcAccel(lsm9DS1Driver_.az);

    auto mx = lsm9DS1Driver_.calcMag(lsm9DS1Driver_.mx);
    auto my = lsm9DS1Driver_.calcMag(lsm9DS1Driver_.my);
    auto mz = lsm9DS1Driver_.calcMag(lsm9DS1Driver_.mz);

    printf("Gyro: %f, %f, %f [deg/s]\n", gx, gy, gz);
    printf("Accel: %f, %f, %f [Gs]\n", ax, ay, az);
    printf("Mag: %f, %f, %f [gauss]\n", mx, my, mz);

    mahony_.update(gx, gy, gz, ax, ay, az, mx, my, mz);
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

