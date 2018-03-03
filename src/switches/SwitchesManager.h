#ifndef AHRS_SWITCHESMANAGER_H
#define AHRS_SWITCHESMANAGER_H

#include <map>
#include <memory>

#include "SwitchesHandle.h"

namespace peripherals
{
    enum SwitchesCode : uint8_t
    {
        UP_SWITCH = 0x10,
        BOTTOM_SWITCH = 0x20,
        OK_SWITCH = 0x30,
        CANCEL_SWITCH = 0x40
    };

    class SwitchesManager
    {
    public:
        SwitchesManager();
        ~SwitchesManager();

        void initialize();
        const std::map<SwitchesCode, std::shared_ptr<SwitchesHandle> > &getSwitches() const;

    private:
        void getSwitchesParametersFromConfig();
        void initializeSwitches(SwitchesCode code, hardware::GPIO gpio);

    private:
        std::map<SwitchesCode, std::shared_ptr<SwitchesHandle> > switches_;

    };
}
#endif
