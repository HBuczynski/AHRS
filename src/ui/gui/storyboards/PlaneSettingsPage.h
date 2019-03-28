#ifndef CALLIBRATIONSETTINGS_H
#define CALLIBRATIONSETTINGS_H

#include <QWidget>
#include <memory>
#include <map>

#include "../PageController.h"
#include "Keyboard.h"
#include "Buttons.h"

namespace Ui {
class PlaneSettingsPage;
}

class PlaneSettingsPage : public QWidget
{
    Q_OBJECT

    enum FieldType : uint8_t
    {
        COMBO_BOX = 0x00,
        TEXT_FIELD,
        CONFIRM_LABEL,
        MENU_LABEL,
        NEXT_LABEL
    };

public:
    explicit PlaneSettingsPage(gui::PageController *controller, QWidget *parent = 0);
    ~PlaneSettingsPage();

    void initialize();

private slots:
    void lineEditClicked();

signals:
    void signalMENUPage();
    void signalCallibrationPage();

private:
    void setupPage();
    void setupSlots();

    void highlightCurrentOption(uint8_t newOption);
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void cancelButton();
    void upButton();
    void downButton();
    void selectButton();

    void setKeyClicked(std::string name);


    static std::string planeNameTextField;
    static std::string planeName;
    std::shared_ptr<Keyboard> keyboard_;
    gui::PageController *controller_;
    Ui::PlaneSettingsPage *ui_;

    bool selectIsPresssed;
    uint8_t currentOption_;
    uint8_t maxOptionsNumber_;

    std::map<FieldType, QWidget*> labels_;
    std::unique_ptr<Buttons> buttons_;
};

#endif // CALLIBRATIONSETTINGS_H
