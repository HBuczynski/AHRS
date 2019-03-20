#include <sstream>
#include "FeederDb.h"

using namespace std;
using namespace database;

FeederDb::FeederDb(const std::string& name)
{
    open(name.c_str());
    createTable();
}

void FeederDb::createTable()
{
    executeCommand(GPS_TABLE);
    executeCommand(IMU_TABLE);
    executeCommand(FEEDER_PROPERTIES);
}

void FeederDb::insertIMU(const IMUData& data)
{
    stringstream stream;
    stream << INSERT_IMU << "(" << mark << data.timestamp << mark << semicolon
                                        << data.accelX  << semicolon
                                        << data.accelY << semicolon
                                        << data.accelZ << semicolon
                                        << data.yaw <<  semicolon
                                        << data.pitch << semicolon
                                        << data.roll << semicolon
                                        << data.heading << ");";

    const auto command = stream.str();
    executeCommand(command);
}

void FeederDb::insertGPS(const gps::GPSData& data)
{
    stringstream stream;
    string time = to_string(data.hour) + ":" + to_string(data.minutes) + ":" + to_string(data.seconds);

    stream << INSERT_GPS << "(" << mark << time << mark << semicolon
                                        << data.latitude << semicolon
                                << mark << data.latitudeDirection << mark << semicolon
                                        << data.longitude << semicolon
                                << mark << data.longitudeDirection << mark << semicolon
                                        << data.altitude << semicolon
                                        << static_cast<int>(data.fixQuality) << semicolon
                                        << static_cast<int>(data.numberOfSatellites) << semicolon
                                << mark << data.receiverWarning << mark << semicolon
                                        << data.groundSpeed << semicolon
                                        << data.course << ");";

    const auto command = stream.str();
    executeCommand(command);
}

void FeederDb::insertFeederProperties(const FeederProperties& feederProperties)
{
    string sql("INSERT INTO FEEDER_PROPERTIES (TIMESTAMP,MODE,BANDWITH,RPI_TEMPERATURE,POWER) "
               "VALUES('129873', 'MASTER', 2.4, 78.6, 100.1);");

    stringstream stream;
    stream << INSERT_FEEDER << "(" << mark << feederProperties.timestamp << mark << semicolon
                                   << mark << feederProperties.mode << mark << semicolon
                                           << feederProperties.bandwith << semicolon
                                           << feederProperties.temperature << semicolon
                                           << feederProperties.power << ");";

    const auto command = stream.str();
    executeCommand(command);
}
