#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H

#include <QWidget>

namespace Ui {
class InformationPage;
}

class InformationPage : public QWidget
{
    Q_OBJECT

public:
    explicit InformationPage(QWidget *parent = 0);
    ~InformationPage();

    void setMasterConnectionEstablished();
    void setMasterConnectionFailed();
    void setSecondaryConnectionEstablished();
    void setSecondaryConnectionFailed();
    void setBITS();
    void setBITSFailed();

private:
    void pageSetup();

    Ui::InformationPage *ui_;
};

#endif // INFORMATIONPAGE_H
