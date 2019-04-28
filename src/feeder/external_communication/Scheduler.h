#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <hsm/State.h>
#include "ProcessManager.h"

namespace communication
{
    class Scheduler
    {
    public:
        Scheduler();

        bool initialize();
        void run();

    private:
        void create();

        std::map<std::string, std::shared_ptr<hsm::State>> states_;
        std::unique_ptr<ProcessManager> processManager_;
    };
}

#endif // SCHEDULER_H
