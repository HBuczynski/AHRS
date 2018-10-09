#ifndef SYSTEMSETUPPAGE_H
#define SYSTEMSETUPPAGE_H

#include <QWidget>

namespace Ui {
class SystemSetupPage;
}

class SystemSetupPage : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSetupPage(QWidget *parent = 0);
    ~SystemSetupPage();

private:
    void setupPage();

    Ui::SystemSetupPage *ui_;
};

#endif // SYSTEMSETUPPAGE_H
