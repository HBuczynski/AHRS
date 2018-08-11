#ifndef AHRS_STATEINTERFACE_H
#define AHRS_STATEINTERFACE_H

namespace machine_state
{
    class CommunicationEventInterface
    {
    public:
        CommunicationEventInterface() { };
        virtual ~CommunicationEventInterface() { };

    };
}

#endif
