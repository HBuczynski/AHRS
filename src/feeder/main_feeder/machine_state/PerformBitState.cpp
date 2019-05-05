#include "PerformBitState.h"

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
      sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH))
{}

void PerformBitState::runEntryEvent()
{}

void PerformBitState::runExitEvent()
{}

void PerformBitState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- CalibrationState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    initializeExternalSharedMemory();

    bitExecutor_.checkConnection();
    bitExecutor_.checkGPS();
    bitExecutor_.checkIMU();

    const auto bitsInfo = bitExecutor_.getBitsInformation();

    BITsResponse response(bitsInfo);
    auto packet = response.getFrameBytes();

    externalSharedMemory_->write(packet);
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
            const std::string message = std::string("-MAIN- CalibrationManager:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- CalibrationManager :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
