#ifndef COCKPITPARAMETERS_H
#define COCKPITPARAMETERS_H

#include <string>

struct CockpitProperties
{
    uint64_t timestamp;

    double temperature;
    double power;

    double core1;
    double core2;
    double core3;
    double core4;

    double first_bandwith;
    double second_bandwith;

    double first_power;
    double second_power;

    double current_net;
};

struct CockpitNetwork
{
    uint64_t timestamp;

    uint32_t networkNumber;
    uint32_t networkMode;

    double bandwith;
};

#endif // COCKPITPARAMETERS_H
