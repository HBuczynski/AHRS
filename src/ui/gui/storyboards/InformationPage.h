#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H

#include "../PageController.h"

#include <QWidget>
#include <memory>

#include "Buttons.h"

namespace Ui {
class InformationPage;
}

class InformationPage : public QWidget
{
    Q_OBJECT

public:
    explicit InformationPage(gui::PageController *controller, QWidget *parent = 0);
    ~InformationPage();

    void initializeExit();
    void initializeContinue();

    void setMasterConnectionEstablished();
    void setMasterConnectionFailed();
    void setSecondaryConnectionEstablished();
    void setSecondaryConnectionFailed();
    void setBITS();
    void setBITSFailed();

signals:
    void signalAHRSPage();
    void signalExitPage();

private:
    void pageSetup();

    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void firstButton();
    void secondButton();
    void thirdButton();
    void fourthButton();

    gui::PageController *controller_;
    std::unique_ptr<Buttons> buttons_;
    Ui::InformationPage *ui_;
};

#endif // INFORMATIONPAGE_H
