#ifndef CallibrationPage_H
#define CallibrationPage_H

#include <memory>

#include <QWidget>
#include "Buttons.h"
#include "../PageController.h"

#include <interfaces/gui/GUICallibrationCommand.h>

namespace Ui {
class CallibrationPage;
}

class CallibrationPage : public QWidget
{
    Q_OBJECT

    enum class CalibrationMode : uint8_t
    {
        IDLE,
        ACCEL_ENABLE,
        ACCEL_DISABLE,
        MAGNETOMETER,
        ELLIPSOID,
        ELLIPSOID_DONE
    };

public:
    explicit CallibrationPage(gui::PageController* controller, QWidget *parent = 0);
    ~CallibrationPage();

    void initialize();
    void setupPage(uint8_t mode);

signals:
    void signalBackPage();

private:
    void setupMaster();
    void setupRedundant();

    void startCallibartion();

    void setAccelerometerParameters();
    void calibrateAccelerometer();

    void setMagnetometerParameters();
    void calibrateMagnetometer();

    void setEllipsoidParameters();
    void calibrateElipsoid();

    std::map<peripherals::SwitchCode, std::string> configureButtons();
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void firstButton();
    void secondButton();
    void thirdButton();
    void fourthButton();

    std::string getAxisName(uint8_t axis);
    std::string getCallibrationStatus(communication::CalibrationStatus status);

    uint8_t mode_;
    communication::CalibrationConfiguration currentConfiguration_;

    CalibrationMode currentMode_;
    Ui::CallibrationPage *ui_;
    gui::PageController* controller_;
    std::unique_ptr<Buttons> buttons_;
};

#endif
