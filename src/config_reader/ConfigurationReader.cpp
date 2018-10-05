#include "ConfigurationReader.h"

#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;
using namespace config;
using namespace hardware;

ConfigurationReader::ConfigurationReader()
{}

ConfigurationReader::~ConfigurationReader()
{}

UIExecutableFiles ConfigurationReader::getUIExecutableFiles(const std::string &filePath)
{
    JSONParser jsonParser(filePath);
    UIExecutableFiles uiExecutableFiles;

    vector<string> configNames;
    configNames.push_back("UI");
    configNames.push_back("ExecutableFiles");

    configNames.push_back("externalCommunicationProcess");
    jsonParser.getString(configNames, uiExecutableFiles.externalCommunicationProcess);

    configNames.pop_back();
    configNames.push_back("guiProcess");
    jsonParser.getString(configNames, uiExecutableFiles.guiProcess);

    return uiExecutableFiles;
}

UIWirelessCommunication ConfigurationReader::getUIWirelessCommunication(const string &filePath)
{
    JSONParser jsonParser(filePath);
    UIWirelessCommunication uiWirelessCommunication;

    vector<string> configNames;
    configNames.push_back("UI");
    configNames.push_back("Wireless");

    configNames.push_back("firstSourcePort");
    jsonParser.getUINT16t(configNames, uiWirelessCommunication.firstSourcePort);

    configNames.pop_back();
    configNames.push_back("firstSourceAddress");
    jsonParser.getString(configNames, uiWirelessCommunication.firstSourceAddress);

    configNames.pop_back();
    configNames.push_back("secondSourcePort");
    jsonParser.getUINT16t(configNames, uiWirelessCommunication.secondSourcePort);

    configNames.pop_back();
    configNames.push_back("secondSourceAddress");
    jsonParser.getString(configNames, uiWirelessCommunication.secondSourceAddress);

    configNames.pop_back();
    configNames.push_back("firstDestinationPort");
    jsonParser.getUINT16t(configNames, uiWirelessCommunication.firstDestinationPort);

    configNames.pop_back();
    configNames.push_back("firstDestinationAddress");
    jsonParser.getString(configNames, uiWirelessCommunication.firstDestinationAddress);

    configNames.pop_back();
    configNames.push_back("secondDestinationPort");
    jsonParser.getUINT16t(configNames, uiWirelessCommunication.secondDestinationPort);

    configNames.pop_back();
    configNames.push_back("secondDestinationAddress");
    jsonParser.getString(configNames, uiWirelessCommunication.secondDestinationAddress);

    return  uiWirelessCommunication;
}

UIMessageQueues ConfigurationReader::getUIMessageQueues(const string &filePath)
{
    JSONParser jsonParser(filePath);
    UIMessageQueues uiMessageQueues;

    vector<string> configNames;
    configNames.push_back("UI");
    configNames.push_back("MessageQueues");

    configNames.push_back("mainProcessQueueName");
    jsonParser.getString(configNames, uiMessageQueues.mainProcessQueueName);

    configNames.pop_back();
    configNames.push_back("firstCommunicationQueueName");
    jsonParser.getString(configNames, uiMessageQueues.firstCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("secondCommunicationQueueName");
    jsonParser.getString(configNames, uiMessageQueues.secondCommunicationQueueName);

    configNames.pop_back();
    configNames.push_back("guiProcessQueueName");
    jsonParser.getString(configNames, uiMessageQueues.guiProcessQueueName);

    configNames.pop_back();
    configNames.push_back("messageQueueNumber");
    jsonParser.getUINT16t(configNames, uiMessageQueues.messageQueueNumber);

    configNames.pop_back();
    configNames.push_back("messageSize");
    jsonParser.getUINT16t(configNames, uiMessageQueues.messageSize);

    return uiMessageQueues;
}

UISharedMemory ConfigurationReader::getUISharedMemory(const string &filePath)
{
    JSONParser jsonParser(filePath);
    UISharedMemory uiSharedMemory;

    vector<string> configNames;
    configNames.push_back("UI");
    configNames.push_back("SharedMemory");

    configNames.push_back("sharedMemoryName");
    jsonParser.getString(configNames, uiSharedMemory.sharedMemoryName);

    configNames.pop_back();
    configNames.push_back("size");
    jsonParser.getUINT16t(configNames, uiSharedMemory.sharedMemorySize);

    return uiSharedMemory;
}

UICommunicationSystemParameters ConfigurationReader::getUICommunicationProcessSystemParameters(const std::string &filePath)
{
    JSONParser jsonParser(filePath);
    UICommunicationSystemParameters uiCommunicationSystemParameters;

    vector<string> configNames;

    /**** FIRST Communication Process ****/
    configNames.push_back("UIFirstCommunication");
    configNames.push_back("mode");

    string tempVariable;
    uint8_t tempProcessNumber;
    jsonParser.getString(configNames, tempVariable);

    if(tempVariable == "MASTER")
    {
        uiCommunicationSystemParameters.firstProcess.mode = UICommunicationMode::MASTER;
    }
    else if(tempVariable == "REDUNDANT")
    {
        uiCommunicationSystemParameters.firstProcess.mode = UICommunicationMode::REDUNDANT;
    }

    configNames.pop_back();
    configNames.push_back("processNumber");
    jsonParser.getUINT8t(configNames, tempProcessNumber);
    uiCommunicationSystemParameters.firstProcess.processNumber = tempProcessNumber;


    /**** SECOND Communication Process ****/
    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("UISecondCommunication");
    configNames.push_back("mode");

    string tempVariable2;
    jsonParser.getString(configNames, tempVariable2);

    if(tempVariable2 == "MASTER")
    {
        uiCommunicationSystemParameters.secondProcess.mode = UICommunicationMode::MASTER;
    }
    else if(tempVariable2 == "REDUNDANT")
    {
        uiCommunicationSystemParameters.secondProcess.mode = UICommunicationMode::REDUNDANT;
    }

    configNames.pop_back();
    configNames.push_back("processNumber");
    jsonParser.getUINT8t(configNames, tempProcessNumber);
    uiCommunicationSystemParameters.secondProcess.processNumber = tempProcessNumber;

    return uiCommunicationSystemParameters;
}

vector<GPIO> ConfigurationReader::getUISwitches(const string &filePath)
{
    JSONParser jsonParser(filePath);
    vector<GPIO> uiSwitches;

    GPIO currentGPIO;
    uint8_t currentPinNumber = 0;
    string mode;
    string pullMode;

    vector<string> configNames;
    configNames.push_back("UIButtons");

    /***  FIRST Button  ***/
    configNames.push_back("FirstButton");
    configNames.push_back("PinNumber");
    jsonParser.getUINT8t(configNames, currentPinNumber);

    configNames.pop_back();
    configNames.push_back("GPIOMode");
    jsonParser.getString(configNames, mode);

    configNames.pop_back();
    configNames.push_back("GPIOPullMode");
    jsonParser.getString(configNames, pullMode);

    currentGPIO.pinNumber = currentPinNumber;
    currentGPIO.pinMode = getGPIOMode(mode);
    currentGPIO.pushPullMode = getGPIOPullMode(pullMode);
    uiSwitches.push_back(currentGPIO);


    /***  SECOND Button  ***/
    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("SecondButton");
    configNames.push_back("PinNumber");
    jsonParser.getUINT8t(configNames, currentPinNumber);

    configNames.pop_back();
    configNames.push_back("GPIOMode");
    jsonParser.getString(configNames, mode);

    configNames.pop_back();
    configNames.push_back("GPIOPullMode");
    jsonParser.getString(configNames, pullMode);

    currentGPIO.pinNumber = currentPinNumber;
    currentGPIO.pinMode = getGPIOMode(mode);
    currentGPIO.pushPullMode = getGPIOPullMode(pullMode);
    uiSwitches.push_back(currentGPIO);

    /***  THIRD Button  ***/
    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("ThirdButton");
    configNames.push_back("PinNumber");
    jsonParser.getUINT8t(configNames, currentPinNumber);

    configNames.pop_back();
    configNames.push_back("GPIOMode");
    jsonParser.getString(configNames, mode);

    configNames.pop_back();
    configNames.push_back("GPIOPullMode");
    jsonParser.getString(configNames, pullMode);

    currentGPIO.pinNumber = currentPinNumber;
    currentGPIO.pinMode = getGPIOMode(mode);
    currentGPIO.pushPullMode = getGPIOPullMode(pullMode);
    uiSwitches.push_back(currentGPIO);

    /***  FOURTH Button  ***/
    configNames.pop_back();
    configNames.pop_back();
    configNames.push_back("FourthButton");
    configNames.push_back("PinNumber");
    jsonParser.getUINT8t(configNames, currentPinNumber);

    configNames.pop_back();
    configNames.push_back("GPIOMode");
    jsonParser.getString(configNames, mode);

    configNames.pop_back();
    configNames.push_back("GPIOPullMode");
    jsonParser.getString(configNames, pullMode);

    currentGPIO.pinNumber = currentPinNumber;
    currentGPIO.pinMode = getGPIOMode(mode);
    currentGPIO.pushPullMode = getGPIOPullMode(pullMode);
    uiSwitches.push_back(currentGPIO);

    return uiSwitches;
}

GPIOMode ConfigurationReader::getGPIOMode(string mode)
{
    if(mode == "IN")
    {
        return GPIOMode::IN;
    }
    else
    {
        return GPIOMode::OUT;
    }
}

GPIOPullMode ConfigurationReader::getGPIOPullMode(string pullMode)
{
    if(pullMode == "DOWN")
    {
        return GPIOPullMode::DOWN;
    }
    else
    {
        return GPIOPullMode::UP;
    }
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
    JSONParser jsonParser(filePath);

    vector<string> names;
    vector<AircraftParameters> planes;
    const Json::Value& value = jsonParser.getBranch(names)["Aircrafts"];

    for(auto iter = value.begin(); iter != value.end(); ++iter)
    {
        AircraftParameters plane;
        string name = iter.key().asString().c_str();

        strncpy(plane.name, name.c_str(), sizeof(plane.name));
        plane.calibrationX = value[name]["calibrationX"].asDouble();
        plane.calibrationY = value[name]["calibrationY"].asDouble();
        plane.calibrationZ = value[name]["calibrationZ"].asDouble();

        planes.push_back(plane);
    }

    return planes;
}

void ConfigurationReader::addAircraftToDatabase(const std::string &filePath, AircraftParameters plane)
{
//    JSONParser jsonParser(filePath);
//
//    vector<string> names;
//    const Json::Value& value = jsonParser.getBranch(names)["Aircrafts"];
}
