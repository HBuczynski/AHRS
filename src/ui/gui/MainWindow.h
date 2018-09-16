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
    
private:
    StoryboardsHandler *storyboardsHandler_;
};

#endif // MAINWINDOW_H
