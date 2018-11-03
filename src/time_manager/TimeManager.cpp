#include "TimeManager.h"

#include <chrono>
#include <iomanip>
#include <memory>

using namespace std;
using namespace std::chrono;
using namespace utility;

std::chrono::system_clock::time_point TimeManager::startTime_ = std::chrono::system_clock::now();;

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

string TimeManager::getTimeSinceStart()
{
    stringstream ss;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto timeSinceStart =  std::chrono::duration_cast<seconds>(currentTime - startTime_).count();

    uint8_t hours = timeSinceStart/3600;
    uint8_t minutes = (timeSinceStart - hours*3600) / 60;
    uint8_t seconds = (timeSinceStart - 3600*hours - 60*minutes);

    if(hours < 10)
    {
        ss << "0" << static_cast<int>(hours) << ":";
    }
    else
    {
        ss << static_cast<int>(hours) << ":";
    }

    if(minutes < 10)
    {
        ss << "0" << static_cast<int>(minutes) << ":";
    }
    else
    {
        ss << static_cast<int>(minutes) << ":";
    }

    if(seconds < 10)
    {
        ss << "0" << static_cast<int>(seconds);
    }
    else
    {
        ss << static_cast<int>(seconds);
    }

    return ss.str();
}
