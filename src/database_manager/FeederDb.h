#ifndef AHRS_FEEDERDB_H
#define AHRS_FEEDERDB_H

#include "Database.h"
#include <common/Measurements.h>

namespace database
{
    class FeederDb : public Database
    {
    public:
        FeederDb(const std::string& name);

        bool openDb();
        bool createTable();

        void insertIMU(const IMUData& data);
        void insertGPS(const GPSData& data);
        void insertFeederProperties(const FeederProperties& feederProperties);

    private:
        const std::string GPS_TABLE = "CREATE TABLE GPS ("
                                    "ID                     INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    "TIMESTAMP              NUMERIC, "
                                    "LATITUDE               DOUBLE  NOT NULL, "
                                    "LATITUDE_DIRECTION     TEXT     NOT NULL, "
                                    "LONGITUDE              DOUBLE     NOT NULL, "
                                    "LONGITUDE_DIRECTION    TEXT     NOT NULL, "
                                    "ALTITUDE               DOUBLE, "
                                    "FIX_QUALITY            INT,"
                                    "SATELLITES             INT,"
                                    "WARNINGS               CHAR(10),"
                                    "GROUND_SPEED           NUMERIC,"
                                    "COURSE                 NUMERIC"
                                    ");";

        const std::string INSERT_GPS = "INSERT INTO GPS (TIMESTAMP,LATITUDE,LATITUDE_DIRECTION,LONGITUDE,LONGITUDE_DIRECTION, ALTITUDE, FIX_QUALITY, "
                                       "SATELLITES, WARNINGS, GROUND_SPEED, COURSE) "
                                       "VALUES";


        const std::string IMU_TABLE = "CREATE TABLE IMU ("
                                      "ID                 INTEGER PRIMARY KEY AUTOINCREMENT, "
                                      "TIMESTAMP          NUMERIC, "
                                      "ACCEL_X            DOUBLE  NOT NULL, "
                                      "ACCEL_Y            DOUBLE  NOT NULL, "
                                      "ACCEL_Z            DOUBLE  NOT NULL, "
                                      "YAW                DOUBLE  NOT NULL, "
                                      "PITCH              DOUBLE  NOT NULL, "
                                      "ROLL               DOUBLE  NOT NULL "
                                      ");";

        const std::string INSERT_IMU = "INSERT INTO IMU (TIMESTAMP,ACCEL_X,ACCEL_Y,ACCEL_Z,YAW, PITCH, ROLL) "
                                       "VALUES";


        const std::string FEEDER_PROPERTIES = "CREATE TABLE FEEDER_PROPERTIES ("
                                              "ID                 INTEGER PRIMARY KEY AUTOINCREMENT, "
                                              "TIMESTAMP          NUMERIC, "
                                              "MODE               TEXT    NOT NULL, "
                                              "BANDWITH           NUMERIC, "
                                              "RPI_TEMPERATURE    NUMERIC, "
                                              "POWER              NUMERIC, "
                                              "PROCESSOR          NUMERIC "
                                              ");";

        const std::string INSERT_FEEDER = "INSERT INTO FEEDER_PROPERTIES (TIMESTAMP,MODE,BANDWITH,RPI_TEMPERATURE,POWER,PROCESSOR) "
                                          "VALUES";
    };
}

#endif //AHRS_FEEDERDB_H
