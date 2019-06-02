#define BOOST_TEST_MODULE UtilityTest

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <config_reader/FeederParameters.h>

#include "../Utility.h"

#include <string>
#include <iostream>

using namespace std;
using namespace utility;

BOOST_AUTO_TEST_SUITE(utility)

        BOOST_AUTO_TEST_CASE(FilesInDir)
        {
            const auto files = Utility::getFilesInDir(config::FEEDER_AIRCRAFTS_DATABASE_PATH);

            for(const auto & file : files)
            {
                cout << file << endl;
            }
        }

        BOOST_AUTO_TEST_CASE(FilesNamesInDir)
        {
            const auto files = Utility::getFilesNamesInDir(config::FEEDER_AIRCRAFTS_DATABASE_PATH);

            for(const auto & file : files)
            {
                cout << file << endl;
            }
        }

        BOOST_AUTO_TEST_CASE(cpu)
        {
            const unsigned measurement_count = 2;
            const unsigned intervalMS = 1000;

            cout << "CPU" << endl;

            for ( unsigned i = 0; i < measurement_count; ++i ) {

                std::vector<float> cpu_loads = Utility::getCPU(intervalMS);
                cout << "get" << endl;
                for ( unsigned i = 0; i < cpu_loads.size(); ++i ) {
                    std::cout << "cpu " << i << " : " << cpu_loads[i] * 100.f << "%" << std::endl;
                }
            }
        }

BOOST_AUTO_TEST_SUITE_END()

