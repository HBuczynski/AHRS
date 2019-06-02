#ifndef AHRS_UTILITY_H
#define AHRS_UTILITY_H

#include <string>
#include <vector>

namespace utility
{
    class Utility
    {
    public:
        static std::vector<std::string> getFilesInDir(const std::string& directoryPath);
        static std::vector<std::string> getFilesNamesInDir(const std::string& directoryPath);
        static std::vector<long long> get_idle();
        static std::vector<float> getCPU(unsigned interval_seconds);
    };
}

#endif //AHRS_UTILITY_H
