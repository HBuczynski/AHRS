#include <sstream>
#include "FeederDb.h"

using namespace std;
using namespace database;

FeederDb::FeederDb(const std::string& name)
    : Database(name)
{}

bool FeederDb::openDb()
{
    return open(name_.c_str());
}

bool FeederDb::createTable()
{
    bool isSuccess = true;
    isSuccess &= executeCommand(HASH_TABLE);
    isSuccess &= executeCommand(GPS_TABLE);
    isSuccess &= executeCommand(IMU_TABLE);
    isSuccess &= executeCommand(FEEDER_PROPERTIES);

    return isSuccess;
}

void FeederDb::insertIMU(const IMUData& data)
{
    stringstream stream;
    stream << INSERT_IMU << "(" << data.timestamp << SEMICOLON
                                << data.accelX  << SEMICOLON
                                << data.accelY << SEMICOLON
                                << data.accelZ << SEMICOLON
                                << data.yaw <<  SEMICOLON
                                << data.pitch << SEMICOLON
                                << data.roll << ");";

    const auto command = stream.str();
    executeCommand(command);
}

void FeederDb::insertGPS(const GPSData& data)
{
    stringstream stream;

    stream << INSERT_GPS << "("               << data.timestamp << SEMICOLON
                                              << data.latitude << SEMICOLON
                                << APOSTROPHE << data.latitudeDirection << APOSTROPHE << SEMICOLON
                                              << data.longitude << SEMICOLON
                                << APOSTROPHE << data.longitudeDirection << APOSTROPHE << SEMICOLON
                                              << data.altitude << SEMICOLON
                                              << static_cast<int>(data.fixQuality) << SEMICOLON
                                              << static_cast<int>(data.numberOfSatellites) << SEMICOLON
                                << APOSTROPHE << data.receiverWarning << APOSTROPHE << SEMICOLON
                                              << data.groundSpeed << SEMICOLON
                                              << data.course << ");";
    const auto command = stream.str();
    executeCommand(command);
}

void FeederDb::insertFeederProperties(const FeederProperties& feederProperties)
{
    stringstream stream;
    stream << INSERT_FEEDER << "("               << feederProperties.timestamp << SEMICOLON
                                                 << static_cast<int>(feederProperties.mode) << SEMICOLON
                                                 << feederProperties.bandwith << SEMICOLON
                                                 << feederProperties.temperature << SEMICOLON
                                                 << feederProperties.power << SEMICOLON
                                                 << feederProperties.core1 << SEMICOLON
                                                 << feederProperties.core2 << SEMICOLON
                                                 << feederProperties.core3 << SEMICOLON
                                                 << feederProperties.core4 << ");";
    const auto command = stream.str();
    executeCommand(command);
}
