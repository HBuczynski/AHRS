#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <string>

namespace utility
{
	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager();

		static std::string getTime();
		static std::string getPreciselyTime();
		static std::string getTimeAndDate();

		static int32_t getYear();
		static int8_t getMonth();
		static int8_t getDay();

		static int8_t getHour();
		static int8_t getMintutes();
		static int8_t getSecond();

		static int64_t getTimeSinceStartInMilisec();
		static int64_t getTimeSinceStartInSec();
	};
}
#endif
