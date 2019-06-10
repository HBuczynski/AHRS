#include "KeyboardHandler.h"

#include <queue>
#include <iostream>

using namespace std;
using namespace hardware;
using namespace peripherals;

KeyboardHandler::KeyboardHandler(QWidget *parent, GPIO gpioProperties, SwitchCode code)
        :   QWidget(parent),
            gpio_(gpioProperties)
{
    key = new QShortcut(this);

    currentKeyID_ = getKey();
    key->setKey(currentKeyID_);
    connect(key, SIGNAL(activated()), this, SLOT(slotShortcut()));
}

KeyboardHandler::~KeyboardHandler()
{
    delete key;
}

void KeyboardHandler::slotShortcut()
{
    if(callback_)
        callback_();
}

void KeyboardHandler::initializeCallbacks(std::function<void()> pressedSwitchCallback,
                                          std::function<void(peripherals::SwitchCode, peripherals::SwitchState)> errorCallback)
{
    callback_ = pressedSwitchCallback;
}

void KeyboardHandler::resetSwitch()
{}

Qt::Key KeyboardHandler::getKey() const noexcept
{
    switch(gpio_.pinNumber)
    {
        case 17 :
        {
            return Qt::Key_Q;
        }
        case 4 :
        {
            return Qt::Key_W;
        }
        case 27 :
        {
            return Qt::Key_E;
        }
        case 22 :
        {
            return Qt::Key_R;
        }
        default:
            return Qt::Key_A;
    }
}
