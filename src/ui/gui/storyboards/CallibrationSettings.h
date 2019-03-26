#ifndef CALLIBRATIONSETTINGS_H
#define CALLIBRATIONSETTINGS_H

#include <QWidget>
#include <memory>

#include "Keyboard.h"
#include "Buttons.h"

namespace Ui {
class CallibrationSettings;
}

class CallibrationSettings : public QWidget
{
    Q_OBJECT

public:
    explicit CallibrationSettings(QWidget *parent = 0);
    ~CallibrationSettings();

    void initialize();

private slots:
    void lineEditClicked();

private:
    void setupPage();
    void setupSlots();

    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void cancelButton();
    void upButton();
    void downButton();
    void selectButton();

    std::shared_ptr<Keyboard> keyboard_;
    Ui::CallibrationSettings *ui_;

    std::unique_ptr<Buttons> buttons_;
};

#endif // CALLIBRATIONSETTINGS_H
