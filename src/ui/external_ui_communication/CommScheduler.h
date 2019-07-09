#ifndef COMMSCHEDULER_H
#define COMMSCHEDULER_H

#include <map>
#include <memory>

#include <hsm/State.h>
#include "ProcessManager.h"

class CommScheduler
{
public:
    CommScheduler(uint8_t mode, uint8_t processNumber);

    bool initialize();
    void run();

private:
    void create(uint8_t mode, uint8_t processNumber);

    std::map<std::string, std::shared_ptr<hsm::State>> states_;
    std::shared_ptr<communication::ProcessManager> procesManagerUI_;
};

#endif // COMMSCHEDULER_H
