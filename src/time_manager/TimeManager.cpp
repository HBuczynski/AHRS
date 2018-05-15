#include "TimeManager.h"

#include <chrono>
#include <iomanip>
#include <memory>

using namespace std;
using namespace std::chrono;
using namespace utility;

TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

string TimeManager::getDate()
{
    std::unique_ptr<char> stringDateTime(new char[stringLength_]);
    std::time_t timeCurrent = std::time(nullptr);
    std::tm *timeLocal = std::localtime(&timeCurrent);
    std::strftime(stringDateTime.get(), stringLength_, "%y.%m.%d", timeLocal);
    std::string stringResult(stringDateTime.get());
    return stringResult;
}

string TimeManager::getTime()
{
	std::unique_ptr<char> stringTime(new char[stringLength_]);
    std::time_t timeCurrent = std::time(nullptr);

    std::tm *timeLocal = std::localtime(&timeCurrent);
    std::strftime(stringTime.get(), stringLength_, "%H.%M.%S", timeLocal);

    std::string stringResult(stringTime.get());

    return stringResult;
}

string TimeManager::getTimeAndDate()
{
	std::unique_ptr<char> stringDateTime(new char[stringLength_]);
    std::time_t timeCurrent = std::time(nullptr);
    std::tm *timeLocal = std::localtime(&timeCurrent);
    std::strftime(stringDateTime.get(), stringLength_, "%y.%m.%d_%H.%M.%S", timeLocal);
    std::string stringResult(stringDateTime.get());
    return stringResult;
}

string TimeManager::getPreciselyTime()
{
    stringstream ss;

    tm localTime;
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    time_t now = std::chrono::system_clock::to_time_t(t);
    localtime_r(&now, &localTime);

    const std::chrono::duration<double> tse = t.time_since_epoch();
    std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;

    ss  << std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
        << std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
        << std::setfill('0') << std::setw(2) << localTime.tm_sec << '.'
        << std::setfill('0') << std::setw(3) << milliseconds;

    return ss.str();
}
