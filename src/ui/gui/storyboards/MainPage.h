#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <memory>

#include <QWidget>
#include "Buttons.h"
#include "../PageController.h"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(gui::PageController* controller, QWidget *parent = 0);
    ~MainPage();

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

    Ui::MainPage *ui_;
    gui::PageController* controller_;
    std::unique_ptr<Buttons> buttons_;
};

#endif // MAINPAGE_H
