#include <iostream>
#include <memory>
#include <chrono>

#include <logger/Logger.h>
#include "ProcessManager.h"

using namespace std;
using namespace chrono;
using namespace utility;
using namespace communication;

void initializeLogger(Logger &logger);
void initializeProcessManager(shared_ptr<ProcessManager> processManager, char *argv[]);

int main(int argc , char *argv[])
{
    if(argc < 4)
    {
        cout << "Invalid arguments number." << endl;
    }

    Logger &logger = Logger::getInstance();
    initializeLogger(logger);

    shared_ptr<ProcessManager> processManager;
    initializeProcessManager(processManager, argv);

    //processManager->run();

    while(1)
    {
        this_thread::sleep_for(milliseconds(1));
    }

    return 0;
}

void initializeLogger(Logger &logger)
{
    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;

    logger.initLogger(struc);
}

void initializeProcessManager(shared_ptr<ProcessManager> processManager, char *argv[])
{
    std::string managementQueueName = argv[1];
    std::string sharedMemoryName = argv[2];

    cout << managementQueueName << endl;

    CommunicationProcessMode status;
    if(string(argv[3]) == "MAIN")
    {
        status = CommunicationProcessMode ::MAIN;

        cout << "MAIN" << endl;
    }
    else if(string(argv[3]) == "REDUNDANT")
    {
        status = CommunicationProcessMode ::REDUNDANT;
    }

    processManager = make_shared<ProcessManager>(managementQueueName, sharedMemoryName, status);
}
