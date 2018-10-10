#ifndef AHRSPAGE_H
#define AHRSPAGE_H

#include <QWidget>
#include <memory>

#include "../PageController.h"
#include "WidgetPFD.h"
#include "WidgetTC.h"
#include "WidgetVSI.h"

#include "Buttons.h"

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

    inline void setRoll( float roll );
    inline void setPitch( float pitch );
    inline void setAltitude( float altitude );
    inline void setPressure( float pressure );
    inline void setAirspeed( float airspeed );
    inline void setMachNo( float machNo );
    inline void setHeading( float heading );
    inline void setClimbRate( float climbRate );

    inline void setTurnRate( float turnRate );
    inline void setSlipSkid( float slipSkid );

signals:
    void signalEXITPage();
    void signalLOGSPage();
    void signalMENUPage();

private:
    void setup();
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void calibrateButton();
    void menuButton();
    void logsButton();
    void exitButton();

    gui::PageController *controller_;

    std::unique_ptr<Buttons> buttons_;
    std::unique_ptr<WidgetTC> widgetTC_;
    std::unique_ptr<WidgetVSI> widgetVSI_;
    std::unique_ptr<WidgetPFD> widgetPFD_;
    Ui::AHRSPage *ui_;

    utility::Logger& logger_;
};

#endif // AHRSPAGE_H
