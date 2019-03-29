#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <memory>

#include <QWidget>
#include <QLabel>
#include "Buttons.h"
#include "../PageController.h"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    enum MainPageOptions
    {
        AHRS,
        PLANE_SETTINGS,
        BITS_INFO,
        EXIT
    };

    Q_OBJECT

public:
    explicit MainPage(gui::PageController* controller, QWidget *parent = 0);
    ~MainPage();

    void initialize();

signals:
    void signalBackPage();
    void signalAHRSPage();
    void signalPlaneSettingsPage();
    void signalBitsInfoPage();
    void signalExitPage();

private:
    void setupPage();
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void highlightCurrentOption(uint8_t newOption);

    void firstButton();
    void secondButton();
    void thirdButton();
    void fourthButton();


    static bool plainIsSet_;
    Ui::MainPage *ui_;
    gui::PageController* controller_;
    std::unique_ptr<Buttons> buttons_;

    uint8_t currentOption_;
    std::vector<QLabel*> labels_;
    const uint8_t MAX_OPTIONS_NUMBER;
};

#endif // MAINPAGE_H
