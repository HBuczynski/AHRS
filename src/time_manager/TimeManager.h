#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <string>
#include <chrono>

namespace utility
{
	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager();

		static std::string getTimeSinceStart();
		static std::string getDate();
		static std::string getTime();
		static std::string getPreciselyTime();
		static std::string getTimeAndDate();

    private:

        static const unsigned int stringLength_ = 100;
        static std::chrono::system_clock::time_point startTime_;
	};
}
#endif

