#ifndef AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H
#define AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H

#include "FlightDataManager.h"
#include "ClientUDP.h"

#include <hsm/HSM.h>
#include <functional>
#include <list>
#include <cstdint>
#include <memory>

namespace communication
{
    class ClientUDPManager : public hsm::HSM
    {
    public:
        ClientUDPManager(const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);
        ~ClientUDPManager();

        // Communication methods
        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t > > getClientList();
        void insertNewClient(std::pair<std::shared_ptr<ClientUDP>, uint8_t > newClient);
        void removeClient(uint8_t id);

        bool broadcast(std::vector<uint8_t> frame);

        void sendToMainProcess(std::vector<uint8_t>& data);
        void registerCallbackToMainProc(std::function<void(std::vector<uint8_t>&)> callback);

    private:
        std::unique_ptr<FlightDataManager> flightDataManager_;

        std::function<void(std::vector<uint8_t>&)> mainProcCallback_;

        std::mutex clientListMutex_;
        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t> > clientList_;

        utility::Logger& logger_;
    };
}
#endif
