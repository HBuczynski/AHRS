#ifndef CALLIBRATIONSETTINGS_H
#define CALLIBRATIONSETTINGS_H

#include <QVBoxLayout>
#include <QLabel>
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
        NEXT_LABEL,
        GENERAL_SETTINGS
    };

public:
    explicit PlaneSettingsPage(gui::PageController *controller,const std::string &planes, QWidget *parent = 0);
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
    void highlightCurrentItem(uint8_t newOption);
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void keyboardButtons();

    void cancelButton();
    void handleSettingsCancel();
    void handleComboBoxCancel();

    void upButton();
    void handleSettingsUP();
    void handleComboBoxUP();

    void downButton();
    void handleSettingsDown();
    void handleComboBoxDown();

    void selectButton();
    void handleSettingsSelect();
    void handleComboBoxSelect();


    void setKeyClicked(std::string name);
    std::vector<std::string> splitPlanes(const std::string& name) const noexcept;

    FieldType currentFieldType_;
    std::vector<std::string> planes_;
    static std::string planeNameTextField;
    static std::string planeName;

    std::shared_ptr<QFrame> planesFrame_;
    std::shared_ptr<QVBoxLayout> planesLayout_;
    std::vector<std::shared_ptr<QLabel>> planesLabels_;
    std::shared_ptr<Keyboard> keyboard_;
    gui::PageController *controller_;
    Ui::PlaneSettingsPage *ui_;

    bool selectIsPresssed;
    uint8_t currentOption_;
    int8_t currentItemInComboBox_;
    uint8_t maxOptionsNumber_;

    std::map<FieldType, QWidget*> labels_;
    std::unique_ptr<Buttons> buttons_;
};

#endif // CALLIBRATIONSETTINGS_H
