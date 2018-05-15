#include <iostream>
#include <memory>
#include <chrono>
#include <fstream>

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

    cout << "In child" << endl;
    Logger &logger = Logger::getInstance();
    initializeLogger(logger);

    shared_ptr<ProcessManager> processManager;
    initializeProcessManager(processManager, argv);

    logger.writeLog(LogType::INFORMATION_LOG, "Child process.");

    string name = string(argv[3]) + ".txt";
    std::ofstream outfile (name.c_str());

    outfile << "my text here lolololo!" << std::endl;

    outfile.close();
    //processManager->run();


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
