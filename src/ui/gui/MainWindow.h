#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMetaType>
#include <QTime>

#include <interfaces/wireless_responses/CalibratingStatusResponse.h>

class StoryboardsHandler;


Q_DECLARE_METATYPE(communication::CalibrationConfiguration)

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
    void setLogsPage();
    void setMenuPage();
    void setConnectingPage();
    void setBITSPage();

    void setPlanesDataset(QString planes);
    void setCallibrationMode(uint8_t mode, communication::CalibrationConfiguration parameters);

private:
    StoryboardsHandler *storyboardsHandler_;
};

#endif // MAINWINDOW_H
