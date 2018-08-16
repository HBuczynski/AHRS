#ifndef AHRS_SWITCHESFACTORY_H
#define AHRS_SWITCHESFACTORY_H

#include <switches/SwitcheHandle.h>

#include <memory>
#include <vector>

namespace main_process
{
    class SwitchesFactory
    {
    public:
        SwitchesFactory();
        ~SwitchesFactory();

        std::vector<std::unique_ptr<peripherals::SwitcheHandle>> getConnectedSwitches();
    };
}

#endif
