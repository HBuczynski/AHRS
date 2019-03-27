#ifndef CALLIBRATIONSETTINGS_H
#define CALLIBRATIONSETTINGS_H

#include <QWidget>
#include <memory>
#include <map>

#include "../PageController.h"
#include "Keyboard.h"
#include "Buttons.h"

namespace Ui {
class CallibrationSettings;
}

class CallibrationSettings : public QWidget
{
    Q_OBJECT

    enum FieldType : uint8_t
    {
        COMBO_BOX = 0x00,
        TEXT_FIELD,
        MENU_LABEL,
        NEXT_LABEL
    };

public:
    explicit CallibrationSettings(gui::PageController *controller, QWidget *parent = 0);
    ~CallibrationSettings();

    void initialize();

private slots:
    void lineEditClicked();

signals:
    void signalMENUPage();

private:
    void setupPage();
    void setupSlots();

    void highlightCurrentOption(uint8_t newOption);
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void cancelButton();
    void upButton();
    void downButton();
    void selectButton();

    std::shared_ptr<Keyboard> keyboard_;
    gui::PageController *controller_;
    Ui::CallibrationSettings *ui_;
    uint8_t currentOption_;
    const uint8_t MAX_OPTIONS_NUMBER;

    std::map<FieldType, QWidget*> labels_;
    std::unique_ptr<Buttons> buttons_;
};

#endif // CALLIBRATIONSETTINGS_H
