#ifndef FEEDERSCHEDULER_H
#define FEEDERSCHEDULER_H

#include <hsm/State.h>
#include "ApplicationManager.h"

namespace main_process
{
    class FeederScheduler
    {
    public:
        FeederScheduler();

        bool initialize();
        void run();

    private:
        void create();

        std::map<std::string, std::shared_ptr<hsm::State>> states_;
        std::unique_ptr<ApplicationManager> applicationManager_;
    };
}

#endif // FEEDERSCHEDULER_H
