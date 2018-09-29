#ifndef AHRSPAGE_H
#define AHRSPAGE_H

#include <QWidget>

#include "WidgetPFD.h"
#include "WidgetTC.h"
#include "WidgetVSI.h"

#include "Buttons.h"

namespace Ui {
class AHRSPage;
}

class AHRSPage : public QWidget
{
    Q_OBJECT

public:
    explicit AHRSPage(QWidget *parent = 0);
    ~AHRSPage();

private:

    void setup();

    Buttons *buttons;
    WidgetTC *widgetTC;
    WidgetVSI *widgetVSI;
    WidgetPFD *widgetPFD_;
    Ui::AHRSPage *ui;
    QFrame *horizontalButtonFrame;
};

#endif // AHRSPAGE_H
