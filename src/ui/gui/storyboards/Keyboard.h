#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <string>
#include <functional>
#include <ctime>
#include <chrono>
#include <QPushButton>

namespace Ui {
class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(std::function<void(std::string)> callback, QWidget *parent = 0);
    ~Keyboard();

    void setInitButton();
    void exit();
    void setRightMove();
    void setLeftMove();

    void setChar();

private slots:
    void lineEditClicked();

    void keypadHandler();
    void symbolChange();
    void keyclose();
    void boardchange();

private:
    void initialize();
    void initializeFont();
    void initializeSlots();

    Ui::Keyboard *ui;

    std::vector<QPushButton*> buttons;

    int16_t keyboardCounter_;

    QPushButton* currentButton_;

    std::chrono::system_clock::time_point previousTime_;
    std::function<void(std::string)> charCallback_;
};

#endif // KEYBOARD_H
