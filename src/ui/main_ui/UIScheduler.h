#ifndef UISCHEDULER_H
#define UISCHEDULER_H

#include <map>
#include <memory>
#include "UIApplicationManager.h"

class UIScheduler
{
public:
    UIScheduler();

    bool initialize();
    void run();

private:
    void create();

    std::map<std::string, std::shared_ptr<hsm::State>> states_;
    std::shared_ptr<main_process::UIApplicationManager> uiApplicationManager_;
};

#endif // UISCHEDULER_H
