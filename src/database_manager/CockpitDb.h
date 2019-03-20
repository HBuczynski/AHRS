#ifndef AHRS_COCKPITDB_H
#define AHRS_COCKPITDB_H

#include "Database.h"
#include <common/Measurements.h>

namespace database
{
    struct CockpitProperties
    {
        std::string timestamp;

        double temperature;
        double power;

        double processorConsumption;
    };

    struct CockpitNetwork
    {
        std::string timestamp;

        std::string networkNumber;
        std::string networkMode;

        double bandwith;
    };

    class CockpitDb : public Database
    {
    public:
        CockpitDb(const std::string& name);

        bool initialize();

        void insertFlightMeasurement(const FlightMeasurements& measurements);
        void insertCockpitProperties(const CockpitProperties& properties);
        void insertCockpitNetwork(const CockpitNetwork& network);

    private:
        bool createTable();

        const std::string FLIGHT_MEASUREMENT_TABLE = "CREATE TABLE FLIGHT_MEASUREMENT ("
                                                            "ID                     INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                            "TIMESTAMP              TEXT    NOT NULL, "
                                                            "ROLL                   DOUBLE  NOT NULL, "
                                                            "PITCH                  DOUBLE  NOT NULL, "
                                                            "YAW                    DOUBLE  NOT NULL, "
                                                            "ALTITUDE               DOUBLE  NOT NULL, "
                                                            "PRESSURE               DOUBLE  NOT NULL, "
                                                            "MACH_NO                DOUBLE  NOT NULL, "
                                                            "GROUND_SPEED           DOUBLE  NOT NULL, "
                                                            "VERTICAL_SPEED         DOUBLE  NOT NULL, "
                                                            "LATITUDE               DOUBLE  NOT NULL, "
                                                            "LATITUDE_DIRECTION     TEXT     NOT NULL, "
                                                            "LONGITUDE              DOUBLE     NOT NULL, "
                                                            "LONGITUDE_DIRECTION    TEXT     NOT NULL, "
                                                            "TURN_COORDINATOR       DOUBLE  NOT NULL, "
                                                            "SLIP_SKID              DOUBLE  NOT NULL"
                                                     ");";

        const std::string FLIGHT_MEASUREMENT_INSERT = "INSERT INTO FLIGHT_MEASUREMENT (TIMESTAMP,ROLL,PITCH,YAW,ALTITUDE,PRESSURE,"
                                                      "MACH_NO,GROUND_SPEED,VERTICAL_SPEED,LATITUDE,LATITUDE_DIRECTION,LONGITUDE,"
                                                      "LONGITUDE_DIRECTION,TURN_COORDINATOR,SLIP_SKID) "
                                                      "VALUES";

        const std::string COCKPIT_PROPERTIES_TABLE = "CREATE TABLE COCKPIT_PROPERTIES ("
                                                          "ID                     INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                          "TIMESTAMP              TEXT    NOT NULL, "
                                                          "RPI_TEMPERATURE    NUMERIC, "
                                                          "POWER              NUMERIC, "
                                                          "PROCESSOR          NUMERIC "
                                                      ");";

        const std::string COCKPIT_PROPERTIES_INSERT = "INSERT INTO COCKPIT_PROPERTIES (TIMESTAMP,RPI_TEMPERATURE,POWER,PROCESSOR) VALUES";


        const std::string COCKPIT_NETWORK_TABLE = "CREATE TABLE NETWORK ("
                                                          "ID                     INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                          "TIMESTAMP              TEXT    NOT NULL, "
                                                          "NUMBER                 INTEGER    NOT NULL, "
                                                          "MODE                   TEXT    NOT NULL, "
                                                          "BANDWITH               DOUBLE"
                                                  ");";

        const std::string COCKPIT_NETWORK_INSERT = "INSERT INTO NETWORK (TIMESTAMP,NUMBER,MODE,BANDWITH) VALUES";
    };
}

#endif //AHRS_COCKPITDB_H
