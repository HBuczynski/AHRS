#ifndef AHRS_PROCESSSCHEDULER_H
#define AHRS_PROCESSSCHEDULER_H

#include <cstdint>
#include <atomic>
#include <spawn.h>

#include <logger/Logger.h>
#include <switches/SwitcheHandle.h>

#include "CommunicationProcessesHandler.h"
#include "SwitchesFactory.h"

namespace main_process
{
    enum ProcessStates : uint8_t
    {
        START,
        INITIALIZATION,
        PLANE_CONFIRMATION,
        MAGNETOMETER_CALIBRATION,
        DATA_ACQUSITION,
        ERROR,
        UP_SWITCH_PRESSED,
        BOTTOM_SWITCH_PRESSED,
        OK_SWITCH_PRESSED,
        CANCEL_SWITCH_PRESSED,
        UP_SWITCH_ERROR,
        BOTTOM_SWITCH_ERROR,
        OK_SWITCH_ERROR,
        CANCEL_SWITCH_ERROR,
        END
    };

    class Scheduler
    {
    public:
        Scheduler();
        ~Scheduler();

        void run();
        void stopRun();
        void initializeCommunicationProcesses(); // public for tests

    private:
        void initialization();
        void initializeGUI();
        void initializeSwitches();
        void initializeMessageQueues();
        void initializeSharedMemory();

        void plainConfirmation();
        void magnetometerCalibration();
        void dataAcquisition();
        void termination();

        void interruptSwitchPressed(peripherals::SwitchesCode switchCode);
        void interruptSwitchError(peripherals::SwitchesCode switchCode);

        std::atomic<bool> runMainProcess_;

        ProcessStates previousState_;
        ProcessStates state_;

        CommunicationProcessesHandler processesHandler;
        std::vector<std::unique_ptr<peripherals::SwitcheHandle>> switches_;

        utility::Logger& logger_;
        const uint8_t FAILURE_NUMBER = 4;
        const uint16_t MESSAGE_QUEUE_DATA_SIZE = 0;
    };
}

#endif //AHRS_PROCESSSCHEDULER_H
