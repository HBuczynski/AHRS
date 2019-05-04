#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H

#include "../PageController.h"

#include <QWidget>
#include <memory>
#include <vector>

#include <interfaces/wireless_responses/BITsResponse.h>
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

    void initialize();
    void update();

    void setMasterConnectionEstablished();
    void setMasterConnectionFailed();
    void setSecondaryConnectionEstablished();
    void setSecondaryConnectionFailed();

    void setGPSMaster();
    void setGPSMasterFailed();
    void setGPSRedundant();
    void setGPSRedundantFailed();

    void setIMUMaster();
    void setIMUSMasterFailed();
    void setIMURedundant();
    void setIMURedundantFailed();
signals:
    void signalAHRSPage();
    void signalMainPage();
    void signalStartAcquisition(std::vector<uint8_t>);

private:
    void pageSetup();

    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void firstButton();
    void secondButton();
    void thirdButton();
    void fourthButton();

    communication::BitsInformation bitsInformation_;

    gui::PageController *controller_;
    std::unique_ptr<Buttons> buttons_;
    Ui::InformationPage *ui_;
};

#endif // INFORMATIONPAGE_H
