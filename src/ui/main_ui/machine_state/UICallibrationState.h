#ifndef UICALLIBRATIONSTATE_H
#define UICALLIBRATIONSTATE_H

#include <hsm/State.h>

#include <vector>
#include <functional>
#include <config_reader/UIParameters.h>

class UICallibrationState : public hsm::State
{
public:
    UICallibrationState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;

    void registerCallbackToExternalComm(std::function<void(std::vector<uint8_t>, config::UICommunicationMode)> callback);

private:
    std::function<void(std::vector<uint8_t>, config::UICommunicationMode)> callback_;
};

#endif // UICALLIBRATIONSTATE_H
