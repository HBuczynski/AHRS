#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

namespace Ui {
class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = 0);
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
};

#endif // KEYBOARD_H
