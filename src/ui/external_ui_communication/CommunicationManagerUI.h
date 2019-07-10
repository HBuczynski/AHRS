#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <time_manager/TimerInterrupt.h>
#include <config_reader/UIParameters.h>
#include <logger/Logger.h>
#include <hsm/HSM.h>
#include <functional>

#include "ServerUDP.h"
#include "ClientTCP.h"

namespace communication
{
    class CommunicationManagerUI : public hsm::HSM, public utility::TimerInterruptNotification
    {
    public:
        CommunicationManagerUI(config::UICommunicationMode mode, uint8_t processNumber, const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);
        ~CommunicationManagerUI();

        bool initializeServer();
        bool connectToFeeder();
        bool reconnect();

        void registerCallbackToMainProc(std::function<void(std::vector<uint8_t>&)> callback);
        void registerCallbackToHM(std::function<void(std::vector<uint8_t>&)> callback);

        void sendCommands(std::unique_ptr<communication::Command> commandIn);
        config::UICommunicationMode getUIMode() const ;

        void setDBParameters(uint32_t hash, const std::string& name);
        void setMode(config::UICommunicationMode mode);

    private:
        void launchTimer();
        void interruptNotification(timer_t timerID);

        config::UICommunicationMode mode_;
        uint8_t processNumber_;
        config::UIWirelessCommunication wirelessCommunicationParameters_;
        utility::TimerInterrupt connectionEstablishingInterrupt_;

        std::unique_ptr<ServerUDP> server_;
        std::unique_ptr<ClientTCP> client_;
        std::function<void(std::vector<uint8_t>&)> mainProcCallback_;
        std::function<void(std::vector<uint8_t>&)> hmCallback_;

        std::atomic<bool> connectionEstablished_;
        utility::Logger& logger_;
    };
}
#endif
