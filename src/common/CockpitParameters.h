#ifndef COCKPITPARAMETERS_H
#define COCKPITPARAMETERS_H

#include <string>

struct CockpitProperties
{
    std::string timestamp;

    double temperature;
    double power;

    double processorConsumption;
};

struct CockpitNetwork
{
    std::string timestamp;

    std::string networkNumber;
    std::string networkMode;

    double bandwith;
};

#endif // COCKPITPARAMETERS_H
