#ifndef GPSPAGE_H
#define GPSPAGE_H

#include <memory>

#include <QWidget>
#include "Buttons.h"
#include "../PageController.h"

namespace Ui {
class GpsPage;
}

class GpsPage : public QWidget
{
    Q_OBJECT

public:
    explicit GpsPage(gui::PageController* controller, QWidget *parent = 0);
    ~GpsPage();

    void initialize();

signals:
    void signalBackPage();

private:
    void setupPage();
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void firstButton();
    void secondButton();
    void thirdButton();
    void fourthButton();

    Ui::GpsPage *ui_;
    gui::PageController* controller_;
    std::unique_ptr<Buttons> buttons_;
};

#endif
