#include "SwitchesFactory.h"

using namespace std;
using namespace peripherals;
using namespace main_process;

SwitchesFactory::SwitchesFactory()
{

}

SwitchesFactory::~SwitchesFactory()
{

}

vector<unique_ptr<SwitcheHandle>> SwitchesFactory::getConnectedSwitches()
{
    //TODO

    return std::vector<std::unique_ptr<peripherals::SwitcheHandle>>();
}
