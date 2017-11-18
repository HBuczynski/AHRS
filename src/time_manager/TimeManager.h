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

    private:
        static const unsigned int stringLength_ = 100;
	};
}
#endif
