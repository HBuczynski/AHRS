#ifndef AHRS_IDLESTATE_H
#define AHRS_IDLESTATE_H

#include "AbstractState.h"

namespace communication
{
    class IdleState : public AbstractState
    {
    public:
        IdleState();
        ~IdleState();
    };
}

#endif