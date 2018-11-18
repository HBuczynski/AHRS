#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../include/LSM9DS1Driver.h"


using namespace std;


BOOST_AUTO_TEST_SUITE( gpio_test )

    BOOST_AUTO_TEST_CASE( reading )
    {
        LSM9DS1Driver imu(IMU_MODE_I2C, 0x6b, 0x1e);
        imu.begin();

        if (!imu.begin()) {
            fprintf(stderr, "Failed to communicate with LSM9DS1.\n");
            exit(EXIT_FAILURE);
        }

        for (;;) {
            while (!imu.gyroAvailable()) ;
            imu.readGyro();
            while(!imu.accelAvailable()) ;
            imu.readAccel();
            while(!imu.magAvailable()) ;
            imu.readMag();

            const auto accelData = imu.getRawAccelData();
            const auto gyroData = imu.getRawGyroData();
            const auto magnetometerData = imu.getRawMagnetometerData();

            printf("Gyro: %f, %f, %f [deg/s]\n", accelData.x, accelData.y, accelData.z);
            printf("Accel: %f, %f, %f [Gs]\n", gyroData.x, gyroData.y, gyroData.z);
            printf("Mag: %f, %f, %f [gauss]\n", magnetometerData.x, magnetometerData.y, magnetometerData.z);
            sleep(1.0);
        }

    }

BOOST_AUTO_TEST_SUITE_END()
