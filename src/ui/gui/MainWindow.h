#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

protected:

    void timerEvent( QTimerEvent *event );
    
private:

    Ui::MainWindow *m_ui;

    int m_timerId;
    int m_steps;
    float m_realTime;
    QTime m_time;
};

#endif // MAINWINDOW_H
