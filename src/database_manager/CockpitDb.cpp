#include <sqlite3.h>
#include <string>
#include <iostream>
#include <sstream>

#include "CockpitDb.h"

using namespace std;
using namespace database;

CockpitDb::CockpitDb(const std::string& name)
    : Database(name)
{}

bool CockpitDb::initialize()
{
    open(name_.c_str());
    return createTable();
}

bool CockpitDb::createTable()
{
    bool isSuccess = true;
    isSuccess &= executeCommand(HASH_TABLE);
    isSuccess &= executeCommand(FLIGHT_MEASUREMENT_TABLE);
    isSuccess &= executeCommand(COCKPIT_NETWORK_TABLE);
    isSuccess &= executeCommand(COCKPIT_PROPERTIES_TABLE);

    return isSuccess;
}

void CockpitDb::insertFlightMeasurement(const FlightMeasurements &measurements)
{
    stringstream stream;
    string time = "temp";
    stream << FLIGHT_MEASUREMENT_INSERT << "(" << APOSTROPHE << time << APOSTROPHE << SEMICOLON
                                                             << measurements.roll << SEMICOLON
                                                             << measurements.pitch << SEMICOLON
                                                             << measurements.heading << SEMICOLON
                                                             << measurements.altitude << SEMICOLON
                                                             << measurements.pressure << SEMICOLON
                                                             << measurements.machNo << SEMICOLON
                                                             << measurements.groundSpeed << SEMICOLON
                                                             << measurements.verticalSpeed << SEMICOLON
                                                             << measurements.latitude << SEMICOLON
                                               << APOSTROPHE << measurements.latitudeDirection << APOSTROPHE << SEMICOLON
                                                             << measurements.longitude << SEMICOLON
                                               << APOSTROPHE << measurements.longitudeDirection << APOSTROPHE << SEMICOLON
                                                             << measurements.turnCoordinator << SEMICOLON
                                                             << measurements.slipSkid << ");";

    const auto command = stream.str();
    executeCommand(command);
}

void CockpitDb::insertCockpitProperties(const CockpitProperties &properties)
{
    stringstream stream;
    stream << COCKPIT_PROPERTIES_INSERT << "(" << APOSTROPHE  << properties.timestamp << APOSTROPHE  << SEMICOLON
                                                              << properties.temperature << SEMICOLON
                                                              << properties.power << SEMICOLON
                                                              << properties.processorConsumption << ");";
    const auto command = stream.str();
    executeCommand(command);
}

void CockpitDb::insertCockpitNetwork(const CockpitNetwork &network)
{
    stringstream stream;
    stream << COCKPIT_NETWORK_INSERT << "(" << APOSTROPHE << network.timestamp << APOSTROPHE << SEMICOLON
                                                          << network.networkNumber << SEMICOLON
                                            << APOSTROPHE << network.networkMode << APOSTROPHE << SEMICOLON
                                                          << network.bandwith << ");";
    const auto command = stream.str();
    executeCommand(command);
}

