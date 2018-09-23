#ifndef CALLIBRATIONSETTINGS_H
#define CALLIBRATIONSETTINGS_H

#include <QWidget>
#include <memory>

#include "Keyboard.h"

namespace Ui {
class CallibrationSettings;
}

class CallibrationSettings : public QWidget
{
    Q_OBJECT

public:
    explicit CallibrationSettings(QWidget *parent = 0);
    ~CallibrationSettings();

private slots:
    void lineEditClicked();

private:
    void setupPage();
    void setupSlots();

    std::shared_ptr<Keyboard> keyboard_;
    Ui::CallibrationSettings *ui;
};

#endif // CALLIBRATIONSETTINGS_H
