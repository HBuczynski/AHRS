#ifndef AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H
#define AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H

#include <waic_client/Client.h>

#include <list>
#include <cstdint>
#include <memory>
#include <utility>

struct CallbackFunctions
{
    std::function<const std::list<std::pair<std::shared_ptr<communication::Client>, uint8_t>> & ()> getClientList;
    std::function<void (std::pair<std::shared_ptr<communication::Client>, uint8_t>) > insertNewClient;
    std::function<void (uint8_t) > removeClient;
};

#endif