#ifndef AHRS_ABSTRACTSTATE_H
#define AHRS_ABSTRACTSTATE_H

#include <string>

#include "CommunicationEventInterface.h"

namespace communication
{
    class ClientUDPManager;

    class AbstractState : public machine_state::CommunicationEventInterface
    {
    public:
        AbstractState(std::string name);
        virtual ~AbstractState();

        const std::string& getName() const;

    protected:
        void setState(ClientUDPManager *machine, AbstractState *state);

        const std::string name_;
    };

}

#endif
