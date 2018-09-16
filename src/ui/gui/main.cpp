#include "MainWindow.h"
#include <QApplication>

#include <logger/Logger.h>
#include "GUIApplicationManager.h"

using namespace std;
using namespace gui;
using namespace chrono;
using namespace utility;

int main( int argc, char *argv[] )
{
    Logger &logger = Logger::getInstance("UI_GUI");

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
        const string message = string("GUI :: Initialization!!");
        logger.writeLog(LogType::INFORMATION_LOG, message);
    }

    QApplication app( argc, argv );

    MainWindow mainWindow;
    GUIApplicationManager applicationManager(&mainWindow);
    
    return app.exec();
}
