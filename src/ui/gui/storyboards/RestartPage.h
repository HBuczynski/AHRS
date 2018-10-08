#ifndef RESTARTPAGE_H
#define RESTARTPAGE_H

#include <QWidget>

namespace Ui {
class RestartPage;
}

class RestartPage : public QWidget
{
    Q_OBJECT

public:
    explicit RestartPage(QWidget *parent = 0);
    ~RestartPage();

private:
    void setupPage();

    Ui::RestartPage *ui;
};

#endif // RESTARTPAGE_H
