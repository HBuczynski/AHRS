#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Utility.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


using namespace std;
using namespace utility;

vector<string> Utility::getFilesInDir(const string &directoryPath)
{
    vector<string> files;

    DIR* dir = opendir(directoryPath.c_str());
    dirent *dirChild;

    while ( (dirChild = readdir(dir)) != NULL )
    {
        if((dirChild->d_type == DT_DIR && dirChild->d_name[0] == '.'))
            continue;

        files.emplace_back(dirChild->d_name);
    }

    closedir(dir);

    return files;
}

vector<string> Utility::getFilesNamesInDir(const string &directoryPath)
{
    auto files = Utility::getFilesInDir(directoryPath);
    const string dot{'.'};

    for(auto& file : files)
    {
        file.erase(file.find(dot));
    }

    return files;
}

std::vector<long long> Utility::get_idle()
{

    //Virtual file, created by the Linux kernel on demand
    std::ifstream in( "/proc/stat" );

    std::vector<long long> result;

    //This might broke if there are not 8 columns in /proc/stat
    boost::regex reg("cpu(\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)");

    std::string line;
    while ( std::getline(in, line) ) {
        boost::smatch match;
        if ( boost::regex_match( line, match, reg ) ) {
            long long idle_time = boost::lexical_cast<long long>(match[5]);

            result.push_back( idle_time );
        }
    }
    return result;
}


std::vector<float> Utility::getCPU(unsigned intervalMS) {

    boost::posix_time::ptime current_time_1 = boost::date_time::microsec_clock<boost::posix_time::ptime>::universal_time();
    std::vector<long long> idle_time_1 = get_idle();

    usleep(intervalMS*1000);

    boost::posix_time::ptime current_time_2 = boost::date_time::microsec_clock<boost::posix_time::ptime>::universal_time();
    std::vector<long long> idle_time_2 = get_idle();

    //We have to measure the time, beacuse sleep is not accurate
    const float total_seconds_elpased = float((current_time_2 - current_time_1).total_milliseconds()) / 1000.f;

    std::vector<float> cpu_loads;

    for ( unsigned i = 0; i < idle_time_1.size(); ++i ) {

        //This might get slightly negative, because our time measurment is not accurate
        const float load = 1.f - float(idle_time_2[i] - idle_time_1[i])/(100.f * total_seconds_elpased);
        cpu_loads.push_back( load );

    }
    return cpu_loads;
}

double Utility::getInterfaceChannel(const std::string& channel)
{
    const uint8_t LINE_BUFSIZE = 128;
    char line[LINE_BUFSIZE];
    FILE *pipe;

#if defined(VIRTUAL_BOARD)
     string cmd = "iwlist wlp1s0 channel | grep Current | grep -o '[0-9][.][[:digit:]]*'";
#else
     string cmd = "iwlist " + channel + " channel | grep Current | grep -o '[0-9][.][[:digit:]]*'";
#endif

    pipe = popen(cmd.c_str(), "r");

    if (pipe == NULL)
        return 0.0;

    fgets(line, LINE_BUFSIZE, pipe);
    pclose(pipe); /* Close the pipe */

    try {
        return std::stod(line);
    }
    catch(std::exception &e) {
        return 0.0;
    }
}

double Utility::getTemp()
{
#if defined(VIRTUAL_BOARD)
    return 0.0;
#else
    const uint8_t LINE_BUFSIZE = 128;
     char line[LINE_BUFSIZE];
     FILE *pipe;

     string cmd = "vcgencmd measure_temp | grep -o '[[:digit:]]*[.][[:digit:]]*'";
     pipe = popen(cmd.c_str(), "r");
     if (pipe == NULL)
         return 0.0;

     fgets(line, LINE_BUFSIZE, pipe);
     pclose(pipe); /* Close the pipe */


     try {
         return std::stod(line);
     }
     catch(std::exception &e) {
         return 0.0;
     }
#endif
}

double Utility::getConnectionLevel(const std::string& channel)
{
     const uint8_t LINE_BUFSIZE = 128;
     char line[LINE_BUFSIZE];
     FILE *pipe;

#if defined(VIRTUAL_BOARD)
     string cmd = "iwconfig wlp1s0 | grep level | cut -c 44- | cut -c1-3";
#else
     string cmd = "iwconfig " + channel + " | grep level | cut -c 44- | cut -c1-3";
#endif
     pipe = popen(cmd.c_str(), "r");
     if (pipe == NULL)
         return 0.0;

     fgets(line, LINE_BUFSIZE, pipe);
     pclose(pipe); /* Close the pipe */

     try {
         return std::stod(line);
     }
     catch(std::exception &e) {
         return 0.0;
     }
}
