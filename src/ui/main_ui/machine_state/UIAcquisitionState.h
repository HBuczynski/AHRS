#ifndef UIACQUISITIONSTATE_H
#define UIACQUISITIONSTATE_H

#include <hsm/State.h>

#include <vector>
#include <functional>
#include <config_reader/UIParameters.h>

class UIAcquisitionState : public hsm::State
{
public:
    UIAcquisitionState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;

    void registerCallbackToExternalComm(std::function<void(std::vector<uint8_t>, config::UICommunicationMode)> callback);

private:
    std::function<void(std::vector<uint8_t>, config::UICommunicationMode)> callback_;
};

#endif // UIACQUISITIONSTATE_H
