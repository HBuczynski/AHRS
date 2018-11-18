#define BOOST_TEST_MODULE GPIOInterfaceTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../include/LSM9DS1.h"


using namespace std;


BOOST_AUTO_TEST_SUITE( gpio_test )

    BOOST_AUTO_TEST_CASE( reading )
    {
        LSM9DS1 imu(IMU_MODE_I2C, 0x6b, 0x1e);
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

            printf("Gyro: %f, %f, %f [deg/s]\n", imu.calcGyro(imu.gx), imu.calcGyro(imu.gy), imu.calcGyro(imu.gz));
            printf("Accel: %f, %f, %f [Gs]\n", imu.calcAccel(imu.ax), imu.calcAccel(imu.ay), imu.calcAccel(imu.az));
            printf("Mag: %f, %f, %f [gauss]\n", imu.calcMag(imu.mx), imu.calcMag(imu.my), imu.calcMag(imu.mz));
            sleep(1.0);

            sleep(1.0);
        }

    }

BOOST_AUTO_TEST_SUITE_END()
