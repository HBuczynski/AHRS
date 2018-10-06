#ifndef BUTTONS_H
#define BUTTONS_H

#include <map>
#include <logger/Logger.h>
#include <functional>

#include <QWidget>
#include "../../../switches/SwitchHandle.h"

namespace Ui {
class Buttons;
}

class Buttons : public QWidget
{
    Q_OBJECT

public:
    explicit Buttons(QWidget *parent = 0);
    ~Buttons();

    void initialize(const std::map<peripherals::SwitchCode, std::string> &names, const std::map<peripherals::SwitchCode, std::function<void()> > &callbackFunctions);

private:
    void setup();
    void initializeText(const std::map<peripherals::SwitchCode, std::string> &names);
    void initializeSwitches(const std::map<peripherals::SwitchCode, std::function<void()> > &callbackFunctions);

    std::string getButtonText(peripherals::SwitchCode switchCode, std::map<peripherals::SwitchCode, std::string> names);
    void switchError(peripherals::SwitchCode code, peripherals::SwitchState state);

    Ui::Buttons *ui;
    std::map<peripherals::SwitchCode, std::unique_ptr<peripherals::SwitchHandle> > switches_;

    utility::Logger& logger_;
};

#endif // BUTTONS_H
