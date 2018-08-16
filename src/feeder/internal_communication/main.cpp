#include <chrono>
#include <thread>
#include <logger/Logger.h>
#include <unistd.h>


using namespace std;
using namespace utility;
using namespace chrono;

int main(int argc , char *argv[])
{
    Logger &logger = Logger::getInstance("Fd_Internal_comm");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    if(logger.isInformationEnable())
    {
        const string message = "Main External Process: Inititialized process. Process id: " + to_string(getpid()) + ". Parent process id: " + to_string(getppid()) + ".";
        logger.writeLog(LogType::INFORMATION_LOG, message);
    }

    while(true)
    {
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    return 0;
}