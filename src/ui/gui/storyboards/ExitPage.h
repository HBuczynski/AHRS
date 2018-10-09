#ifndef EXITPAGE_H
#define EXITPAGE_H

#include <QLabel>
#include <QWidget>
#include <vector>

#include "Buttons.h"
#include "../PageController.h"

namespace Ui {
class ExitPage;
}

class ExitPage : public QWidget
{
    Q_OBJECT

public:
    explicit ExitPage(/*gui::PageController* controller,*/ QWidget *parent = 0);
    ~ExitPage();

    void initialize();

signals:
    void informPrev();

private:
    void setupPage();

    void highlightCurrentOption(uint8_t newOption);

    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void firstButton();
    void leftArrow();
    void submit();
    void rightArrow();

    uint8_t currentOption_;
    Buttons *buttons;
    Ui::ExitPage *ui;
    gui::PageController* controller_;

    const uint8_t MAX_OPTIONS_NUMBER;

    std::vector<QLabel*> labels_;
};

#endif // EXITPAGE_H
