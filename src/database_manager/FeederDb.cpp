#include <sstream>
#include "FeederDb.h"

using namespace std;
using namespace database;

FeederDb::FeederDb(const std::string& name)
    : Database(name)
{}

bool FeederDb::initialize()
{
    open(name_.c_str());
    return createTable();
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
    stream << INSERT_IMU << "(" << APOSTROPHE << data.timestamp << APOSTROPHE << SEMICOLON
                                              << data.accelX  << SEMICOLON
                                              << data.accelY << SEMICOLON
                                              << data.accelZ << SEMICOLON
                                              << data.yaw <<  SEMICOLON
                                              << data.pitch << SEMICOLON
                                              << data.roll << SEMICOLON; //TO DO
                                              //<< data.heading << ");";
    const auto command = stream.str();
    executeCommand(command);
}

void FeederDb::insertGPS(const GPSData& data)
{
    stringstream stream;
    string time = to_string(data.hour) + ":" + to_string(data.minutes) + ":" + to_string(data.seconds);

    stream << INSERT_GPS << "(" << APOSTROPHE << time << APOSTROPHE << SEMICOLON
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
    stream << INSERT_FEEDER << "(" << APOSTROPHE << feederProperties.timestamp << APOSTROPHE << SEMICOLON
                                   << APOSTROPHE << feederProperties.mode << APOSTROPHE << SEMICOLON
                                                 << feederProperties.bandwith << SEMICOLON
                                                 << feederProperties.temperature << SEMICOLON
                                                 << feederProperties.power << SEMICOLON
                                                 << feederProperties.processorConsumption << ");";
    const auto command = stream.str();
    executeCommand(command);
}
