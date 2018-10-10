#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <memory>

#include <QWidget>
#include "Buttons.h"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

private:
    void setupPage();

    Ui::MainPage *ui_;
    std::unique_ptr<Buttons> buttons_;
};

#endif // MAINPAGE_H
