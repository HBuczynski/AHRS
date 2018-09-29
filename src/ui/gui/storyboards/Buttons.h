#ifndef BUTTONS_H
#define BUTTONS_H

#include <QWidget>

namespace Ui {
class Buttons;
}

class Buttons : public QWidget
{
    Q_OBJECT

public:
    explicit Buttons(QWidget *parent = 0);
    ~Buttons();

private:
    void setup();

    Ui::Buttons *ui;
};

#endif // BUTTONS_H
