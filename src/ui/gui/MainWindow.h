#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

class StoryboardsHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    void setWelcomePage();
    void setAHRSPage();
    void setCallibrationSettingPage();
    void setSystemSetupPage();
    void setRestartPage();
    void setExitPage();
    
private:
    StoryboardsHandler *storyboardsHandler_;
};

#endif // MAINWINDOW_H
