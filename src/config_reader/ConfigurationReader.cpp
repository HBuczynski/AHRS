#include "ConfigurationReader.h"

using namespace std;
using namespace config;

ConfigurationReader::ConfigurationReader()
{}

ConfigurationReader::~ConfigurationReader()
{}

UIWirelessCommunication ConfigurationReader::getUIWirelessCommunication(const string &filePath)
{
    JSONParser jsonParser(filePath);
    UIWirelessCommunication feederParameters;

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("Wireless");

    configNames.push_back("sourcePort");

    string lol = "trolo";

    jsonParser.getString(configNames, lol);

    return  feederParameters;
}

UIMessageQueues ConfigurationReader::getUIMessageQueues(const string &filePath)
{
    UIMessageQueues parameters;

    return parameters;
}

UISharedMemory ConfigurationReader::getUISharedMemory(const string &filePath)
{
    UISharedMemory parameters;

    return parameters;
}

UICommunicationSystemParameters ConfigurationReader::getUICommunicationProcessSystemParameters(const std::string &filePath)
{
    UICommunicationSystemParameters uiCommunicationSystemParameters;

    return uiCommunicationSystemParameters;
}

void ConfigurationReader::setUICommunicationMode(const string &filePath, uint8_t processNumber, UICommunicationMode mode)
{
    JSONParser jsonParser(filePath);

    if(mode == UICommunicationMode ::REDUNDANT)
    {

    }
    else if (mode == UICommunicationMode::MASTER)
    {

    }
}

FeederExternalWireless ConfigurationReader::getFeederExternalWireless(const string &filePath)
{
    FeederExternalWireless feederExternalWireless;
    JSONParser jsonParser(filePath);

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("ExternalWireless");

    configNames.push_back("firstPort");
    jsonParser.getUINT16t(configNames, feederExternalWireless.firstPort);

    configNames.pop_back();
    configNames.push_back("secondPort");
    jsonParser.getUINT16t(configNames, feederExternalWireless.secondPort);

    configNames.pop_back();
    configNames.push_back("userNumber");
    jsonParser.getUINT8t(configNames, feederExternalWireless.maxUserNumber);

    return feederExternalWireless;
}

FeederInternalWireless ConfigurationReader::getFeederInternalWireless(const string &filePath)
{
    FeederInternalWireless feederInternalWireless;
    JSONParser jsonParser(filePath);

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("InternalWireless");

    configNames.push_back("firstPort");
    jsonParser.getUINT16t(configNames, feederInternalWireless.firstPort);

    configNames.pop_back();
    configNames.push_back("secondPort");
    jsonParser.getUINT16t(configNames, feederInternalWireless.secondPort);

    configNames.pop_back();
    configNames.push_back("firstAddress");
    jsonParser.getString(configNames, feederInternalWireless.firstAddress);

    configNames.pop_back();
    configNames.push_back("secondAddress");
    jsonParser.getString(configNames, feederInternalWireless.secondAddress);

    return feederInternalWireless;
}

FeederMessageQueues ConfigurationReader::getFeederMessageQueues(const string &filePath)
{
    FeederMessageQueues feederMessageQueues;
    JSONParser jsonParser(filePath);

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("MessageQueues");

    configNames.push_back("mainProcessQueueName");
    jsonParser.getString(configNames, feederMessageQueues.mainProcessQueueName);

    configNames.pop_back();
    configNames.push_back("externalCommunicationQueueName");
    jsonParser.getString(configNames, feederMessageQueues.externalCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("internalCommunicationQueueName");
    jsonParser.getString(configNames, feederMessageQueues.internalCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("messageQueueNumber");
    jsonParser.getUINT16t(configNames, feederMessageQueues.messageQueueNumber);

    configNames.pop_back();
    configNames.push_back("messageSize");
    jsonParser.getUINT16t(configNames, feederMessageQueues.messageSize);

    return feederMessageQueues;
}

FeederSharedMemory ConfigurationReader::getFeederSharedMemory(const string &filePath)
{
    FeederSharedMemory feederSharedMemory;
    JSONParser jsonParser(filePath);

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("SharedMemory");

    configNames.push_back("externalMemoryName");
    jsonParser.getString(configNames, feederSharedMemory.externalMemoryName);

    configNames.pop_back();
    configNames.push_back("internalMemoryName");
    jsonParser.getString(configNames, feederSharedMemory.internalMemoryName);

    configNames.pop_back();
    configNames.push_back("size");
    jsonParser.getUINT16t(configNames, feederSharedMemory.sharedMemorySize);

    return feederSharedMemory;
}

FeederType ConfigurationReader::getFeederType(const string &filePath)
{
    FeederType feederType;
    JSONParser jsonParser(filePath);

    vector<string> configNames;
    configNames.push_back("FeederSystem");
    configNames.push_back("mode");

    std::string tempVariable;
    jsonParser.getString(configNames, tempVariable);

    if(tempVariable == "MASTER")
    {
        feederType.mode = FeederMode::MASTER;
    }
    else if(tempVariable == "REDUNDANT")
    {
        feederType.mode = FeederMode::REDUNDANT;
    }

    configNames.pop_back();
    configNames.push_back("processNumber");

    jsonParser.getUINT8t(configNames, feederType.processNumber);

    return feederType;
}

void ConfigurationReader::setFeederSystemValue(const string &filePath, FeederMode mode)
{
    JSONParser jsonParser(filePath);

    vector<string> configNames;
    configNames.push_back("FeederSystem");
    configNames.push_back("mode");

    if(mode == FeederMode::REDUNDANT)
    {
        string mode("REDUNDANT");
        jsonParser.setString(configNames, mode);
    }
    else if (mode == FeederMode::MASTER)
    {
        string mode("MASTER");
        jsonParser.setString(configNames, mode);
    }
}

FeederExecutableFiles ConfigurationReader::getFeederExecutableFiles(const std::string &filePath)
{
    FeederExecutableFiles feederExecutableFiles;
    JSONParser jsonParser(filePath);

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("ExecutableFiles");

    configNames.push_back("externalCommunication");
    jsonParser.getString(configNames, feederExecutableFiles.externalCommunication);

    configNames.pop_back();
    configNames.push_back("internalCommunication");
    jsonParser.getString(configNames, feederExecutableFiles.internalCommunication);

    return feederExecutableFiles;
}

std::vector<AircraftParameters> ConfigurationReader::getAircraftDatabase(const std::string &filePath)
{
    return vector<AircraftParameters>();
}