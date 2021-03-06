#ifndef PERFORMBITSTATE_H
#define PERFORMBITSTATE_H

#include <thread>

#include <functional>
#include <hsm/State.h>
#include <config_reader/FeederParameters.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>

#include <hal/include/BITExecutor.h>

class PerformBitState : public hsm::State
{
public:
    PerformBitState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;

    void approveUDPBits() noexcept;

    void initializeExternalSharedMemory();
    void registerCallbackToExternalComm(std::function<void(std::vector<uint8_t>)> callback);

private:
    BITExecutor bitExecutor_;

    void startBITs();

    std::atomic<bool> runBits_;
    std::thread runBitsThread_;

    std::function<void(std::vector<uint8_t>)> callback_;

    config::FeederSharedMemory sharedMemoryParameters_;
    std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;
};

#endif // PERFORMBITSTATE_H
