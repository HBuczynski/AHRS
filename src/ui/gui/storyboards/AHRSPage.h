#ifndef AHRSPAGE_H
#define AHRSPAGE_H

#include <QWidget>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <config_reader/UIParameters.h>
#include "../../../common/Measurements.h"

    #include "../PageController.h"
#include "WidgetPFD.h"
#include "WidgetTC.h"
#include "WidgetVSI.h"

#include "Buttons.h"

#include <QTimer>

namespace Ui {
class AHRSPage;
}

class AHRSPage : public QWidget
{
    Q_OBJECT

public:
    explicit AHRSPage(gui::PageController *controller, QWidget *parent = 0);
    ~AHRSPage();

    void initialize();

    void setRoll( float roll );
    void setPitch( float pitch );
    void setAltitude( float altitude );
    void setPressure( float pressure );
    void setAirspeed( float airspeed );
    void setMachNo( float machNo );
    void setHeading( float heading );
    void setClimbRate( float climbRate );

    void setTurnRate( float turnRate );
    void setSlipSkid( float slipSkid );

    void setTimeSinceStart(std::string time);
    void update();

private slots:
    void acquireFlightData();
    void changeONExitPage();
    void changeONLogsPage();
    void changeONMainPage();


signals:
    void signalEXITPage();
    void signalLOGSPage();
    void signalMENUPage();

private:
    void setup();
    void initializeSharedMemory();
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void calibrateButton();
    void menuButton();
    void logsButton();
    void exitButton();

    void startAcqTimer();
    void stopAcqTimer();
    void handleFlightDataCommand(const FlightMeasurements& measurements);

    config::UISharedMemory uiSharedMemoryParameters_;

    QTimer acqTimer_;
    std::unique_ptr<communication::SharedMemoryWrapper> sharedMemory_;

    gui::PageController *controller_;

    std::unique_ptr<Buttons> buttons_;
    std::unique_ptr<WidgetTC> widgetTC_;
    std::unique_ptr<WidgetVSI> widgetVSI_;
    std::unique_ptr<WidgetPFD> widgetPFD_;
    Ui::AHRSPage *ui_;

    utility::Logger& logger_;
};

#endif // AHRSPAGE_H
