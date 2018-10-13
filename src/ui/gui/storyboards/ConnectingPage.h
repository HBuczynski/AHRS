#ifndef CONNECTINGPAGE_H
#define CONNECTINGPAGE_H

#include <QWidget>

namespace Ui {
class ConnectingPage;
}

class ConnectingPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectingPage(QWidget *parent = 0);
    ~ConnectingPage();

private:
    void setupPage();

    Ui::ConnectingPage *ui_;
};

#endif // CONNECTINGPAGE_H
