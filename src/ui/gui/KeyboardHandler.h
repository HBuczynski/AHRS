#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QShortcut>
#include <QWidget>

#include <switches/SwitchHandle.h>

class KeyboardHandler : public QWidget, public peripherals::SwitchHandle
{
Q_OBJECT
public:
    KeyboardHandler(QWidget *parent, hardware::GPIO gpioProperties, peripherals::SwitchCode code);
    ~KeyboardHandler();

    virtual void resetSwitch() override ;
    virtual void initializeCallbacks(std::function< void() > pressedSwitchCallback,
                                     std::function< void(peripherals::SwitchCode, peripherals::SwitchState) > errorCallback) override;

private slots:
    void slotShortcut();

    Qt::Key getKey() const noexcept;

private:
    hardware::GPIO gpio_;

    Qt::Key currentKeyID_;
    QShortcut *key;
    std::function<void()> callback_;
};

#endif // KEYBOARDHANDLER_H
