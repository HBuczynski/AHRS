#include "ConfigurationReader.h"

using namespace std;
using namespace config;

ConfigurationReader::ConfigurationReader()
{}

ConfigurationReader::~ConfigurationReader()
{}

UIWirelessCommunication ConfigurationReader::getUIWirelessCommunication(const std::string &filePath)
{
    JSONParser jsonParser(filePath);
    UIWirelessCommunication feederParameters;

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("Wireless");

    configNames.push_back("sourcePort");

    std::string lol = "trolo";

    jsonParser.getString(configNames, lol);
}

UIMessageQueues ConfigurationReader::getUIMessageQueues(const std::string &filePath)
{
    UIMessageQueues parameters;

    return parameters;
}

UISharedMemory ConfigurationReader::getUISharedMemory(const std::string &filePath)
{
    UISharedMemory parameters;

    return parameters;
}

FeederExternalWireless ConfigurationReader::getFeederExternalWireless(const std::string &filePath)
{
    FeederExternalWireless  parameters;

    return parameters;
}

FeederInternalWireless ConfigurationReader::getFeederInternalWireless(const std::string &filePath)
{
    FeederInternalWireless  parameters;

    return parameters;
}

FeederMessageQueues ConfigurationReader::getFeederMessageQueues(const std::string &filePath)
{
    FeederMessageQueues  parameters;

    return parameters;
}

FeederSharedMemory ConfigurationReader::getFeederSharedMemory(const std::string &filePath)
{
    FeederSharedMemory  parameters;

    return parameters;
}

FeederType ConfigurationReader::getFeederType(const std::string &filePath)
{
    FeederType feederType;

    return feederType;
}

void ConfigurationReader::setUICommunicationMode(const std::string &filePath, uint8_t processNumber, UICommunicationMode mode)
{
    JSONParser jsonParser(filePath);

    if(mode == UICommunicationMode ::REDUNDANT)
    {

    }
    else if (mode == UICommunicationMode::MASTER)
    {

    }
}

void ConfigurationReader::setFeederSystemValue(const std::string &filePath, FeederMode mode)
{
    JSONParser jsonParser(filePath);

    if(mode == FeederMode::REDUNDANT)
    {

    }
    else if (mode == FeederMode::MASTER)
    {

    }
}

/*
FeederParameters ConfigurationReader::getFeederParameters(const std::string &path)
{
    JSONParser jsonParser(path);
    FeederParameters feederParameters;

    vector<string> configNames;
    configNames.push_back("Feeder");
    configNames.push_back("Wireless");

    configNames.push_back("sourcePort");
    jsonParser.getUINT16t(configNames, feederParameters.sourcePort);

    configNames.pop_back();
    configNames.push_back("userNumber");
    jsonParser.getUINT8t(configNames, feederParameters.maxUserNumber);

    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("MessageQueues");

    configNames.push_back("mainProcessQueueName");
    jsonParser.getString(configNames, feederParameters.mainProcessQueueName);

    configNames.pop_back();
    configNames.push_back("externalCommunicationQueueName");
    jsonParser.getString(configNames, feederParameters.externalCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("internalCommunicationQueueName");
    jsonParser.getString(configNames, feederParameters.internalCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("messageSize");
    jsonParser.getUINT16t(configNames, feederParameters.messageSize);

    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("SharedMemory");

    configNames.push_back("externalMemoryName");
    jsonParser.getString(configNames, feederParameters.externalMemoryName);

    configNames.pop_back();
    configNames.push_back("internalMemoryName");
    jsonParser.getString(configNames, feederParameters.internalMemoryName);

    configNames.pop_back();
    configNames.push_back("size");
    jsonParser.getUINT16t(configNames, feederParameters.sharedMemorySize);

    return feederParameters;
}

UIParameters ConfigurationReader::getUIParameters(const std::string &path)
{
    JSONParser jsonParser(path);
    UIParameters uiParameters;

    vector<string> configNames;
    configNames.push_back("UI");
    configNames.push_back("Wireless");

    configNames.push_back("sourcePort");
    jsonParser.getUINT16t(configNames, uiParameters.sourcePort);

    configNames.pop_back();
    configNames.push_back("sourceAddress");
    jsonParser.getString(configNames, uiParameters.sourceAddress);

    configNames.pop_back();
    configNames.push_back("destinationPort");
    jsonParser.getUINT16t(configNames, uiParameters.destinationPort);

    configNames.pop_back();
    configNames.push_back("destinationAddress");
    jsonParser.getString(configNames, uiParameters.destinationAddress);

    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("MessageQueues");

    configNames.push_back("mainProcessQueueName");
    jsonParser.getString(configNames, uiParameters.mainProcessQueueName);

    configNames.pop_back();
    configNames.push_back("mainCommunicationQueueName");
    jsonParser.getString(configNames, uiParameters.mainCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("redundantCommunicationQueueName");
    jsonParser.getString(configNames, uiParameters.redundantCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("guiProcessQueueName");
    jsonParser.getString(configNames, uiParameters.guiProcessQueueName);

    configNames.pop_back();
    configNames.push_back("messageSize");
    jsonParser.getUINT16t(configNames, uiParameters.messageSize);

    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("SharedMemory");

    configNames.push_back("dataSharedMemory");
    jsonParser.getString(configNames, uiParameters.dataSharedMemory);

    configNames.pop_back();
    configNames.push_back("size");
    jsonParser.getUINT16t(configNames, uiParameters.sharedMemorySize);

    return uiParameters;
}*/