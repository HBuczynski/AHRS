#ifndef BUTTONS_H
#define BUTTONS_H

#include <map>
#include <logger/Logger.h>
#include <functional>

#include <QWidget>
#include <switches/SwitcheHandle.h>

namespace Ui {
class Buttons;
}

class Buttons : public QWidget
{
    Q_OBJECT

public:
    explicit Buttons(QWidget *parent = 0);
    ~Buttons();

    void initialize(const std::map<peripherals::SwitchesCode, std::string> &names, const std::map<peripherals::SwitchesCode, std::function<void()> > &callbackFunctions);

private:
    void setup();
    void initializeText(const std::map<peripherals::SwitchesCode, std::string> &names);
    void initializeSwitches(const std::map<peripherals::SwitchesCode, std::function<void()> > &callbackFunctions);

    std::string getButtonText(peripherals::SwitchesCode switchCode, std::map<peripherals::SwitchesCode, std::string> names);
    void switchError(peripherals::SwitchState state);

    Ui::Buttons *ui;
    std::map<peripherals::SwitchesCode, std::unique_ptr<peripherals::SwitcheHandle> > switches_;

    utility::Logger& logger_;
};

#endif // BUTTONS_H
