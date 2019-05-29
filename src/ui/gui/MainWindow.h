#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMetaType>
#include <QTime>

#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_responses/BITsResponse.h>

class StoryboardsHandler;


Q_DECLARE_METATYPE(communication::CalibrationConfiguration)
Q_DECLARE_METATYPE(communication::BitsInformation)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

public slots:
    void setWelcomePage();
    void setAHRSPage();
    void setSettingPage();
    void setSystemSetupPage();
    void setRestartPage();
    void setExitPage();
    void setGpsPage();
    void setMenuPage();
    void setConnectingPage();

    void setBITSPage(communication::BitsInformation info);
    void setPlanesDataset(QString planes);
    void setCallibrationMode(uint8_t mode, communication::CalibrationConfiguration parameters);

private:
    StoryboardsHandler *storyboardsHandler_;
};

#endif // MAINWINDOW_H
