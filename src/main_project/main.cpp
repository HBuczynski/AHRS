#include <iostream>
#include <logger/Logger.h>

using namespace std;
using namespace utility;

int main()
{
    Logger &log = Logger::getInstance();

    InitLogStructure struc;

    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;

    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;

    log.initLogger(struc);

    log.writeLog(INFORMATION_LOG, "Logger testing");

    return 0;
}
