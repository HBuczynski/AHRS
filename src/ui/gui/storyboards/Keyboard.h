#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <string>
#include <functional>

namespace Ui {
class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(std::function<void(std::string)> callback, QWidget *parent = 0);
    ~Keyboard();

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
    std::function<void(std::string)> charCallback_;
};

#endif // KEYBOARD_H
