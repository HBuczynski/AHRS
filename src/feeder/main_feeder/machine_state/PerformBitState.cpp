#include "PerformBitState.h"

#include <interfaces/communication_process_feeder/UDPBitsNotification.h>
#include <interfaces/wireless_responses/BITsResponse.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <utility/Utility.h>


using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;


PerformBitState::PerformBitState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent),
      runBits_(true),
      sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH))
{}

void PerformBitState::runEntryEvent()
{}

void PerformBitState::runExitEvent()
{
    runBits_ = false;

    if(runBitsThread_.joinable())
        runBitsThread_.join();
}

void PerformBitState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- PerformBitState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    initializeExternalSharedMemory();

    runBits_ = true;
    runBitsThread_ = thread(&PerformBitState::startBITs, this);
}

void PerformBitState::approveUDPBits() noexcept
{
    bitExecutor_.approveConnection();
}

void PerformBitState::initializeExternalSharedMemory()
{
    try
    {
        externalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- PerformBitState:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- PerformBitState :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void PerformBitState::registerCallbackToExternalComm(std::function<void(std::vector<uint8_t>)> callback)
{
    callback_ = callback;
}

void PerformBitState::startBITs()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- PerformBitState :: Run BIT thread.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    // Run UDP msg
    UDPBitsNotification notification(BITS_ACTION::SEND_DEMAND);
    auto packet = notification.getFrameBytes();
    callback_(packet);

    while(runBits_)
    {
        bitExecutor_.checkConnection();
        bitExecutor_.checkGPS();
        bitExecutor_.checkIMU();

        auto bitsInfo = bitExecutor_.getBitsInformation();
        bool condition = (bitsInfo.m_communication == 25)
                         && (bitsInfo.m_gps == 25)
                         && (bitsInfo.m_imu == 25);

        if(condition)
        {
            bitsInfo.progress = 1;
            runBits_ = false;
        }
        else
        {
            bitsInfo.progress = 0;
        }

        BITsResponse response(bitsInfo);
        auto packet = response.getFrameBytes();
        externalSharedMemory_->write(packet);
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- PerformBitState :: STOP BIT thread.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
