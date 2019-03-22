#ifndef GPS_TEST_GPSINTERFACE_H
#define GPS_TEST_GPSINTERFACE_H

#include <chrono>
#include <atomic>

#include "NMEAParser.h"
#include <hal/include/RS232Interface.h>
#include <hal/include/Switch.h>

#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"              ///<  1 Hz
#define PMTK_SET_NMEA_UPDATE_2HZ  "$PMTK220,500*2B"               ///<  2 Hz
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"               ///<  5 Hz
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"               ///< 10 Hz

namespace gps
{
    enum class GPSStatus : uint8_t
    {
        FIXED,
        SEARCHING_SATELLITES,
        INITIALISED_TIME_EXCEED
    };

    typedef std::chrono::system_clock::time_point TimePoint;

    class GPSAdafruitInterface
    {
    public:
        GPSAdafruitInterface(const std::string& deviceName);

        void initialize();
        GPSStatus getStatus();

        GPSData getData();

    private:
        static void interruptCallback(int gpio, int level, uint32_t tick, void *userdata);

        void interruptHandle();

        hardware::Switch fixedSwitch_;

        TimePoint start_;
        TimePoint end_;

        RS232Interface rs232Interface_;
        std::atomic<GPSStatus> gpsStatus_;

        const uint32_t FIXED_THRESHOLD = 10000;
        const uint8_t SENTENCE_MIN_THRESHOLD = 60;
    };
}

#endif //GPS_TEST_GPSINTERFACE_H
