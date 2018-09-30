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

    void initialize(std::map<peripherals::SwitchesCode, std::string> name, std::map<peripherals::SwitchesCode, std::function<void()> > callbackFunctions);

private:
    void setup();
    void initializeText();
    std::string getButtonText(peripherals::SwitchesCode switchCode);

    Ui::Buttons *ui;
    std::map<peripherals::SwitchesCode, std::string> name_;
    std::map<peripherals::SwitchesCode, std::function<void()> > callbackFunctions_;

    utility::Logger& logger_;
};

#endif // BUTTONS_H
