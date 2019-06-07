#ifndef HMNODES_H
#define HMNODES_H

#include <cstdint>

#define HM_INTERVAL_MS 15000

enum class HMNodes : uint8_t
{
    MAIN_UI,
    GUI,
    EXTERNAL_UI_COMM_1,
    EXTERNAL_UI_COMM_2,

    MAIN_FEEDER,
    EXTERNAL_FEEDER_COMM,
    INTERNAL_FEEDER_COMM
};

#endif // HMNODES_H
