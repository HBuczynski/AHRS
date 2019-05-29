#ifndef GPSPAGE_H
#define GPSPAGE_H

#include <memory>

#include <QWidget>
#include "Buttons.h"
#include "../PageController.h"

#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <config_reader/UIParameters.h>
#include "../../../common/Measurements.h"

#include <QTimer>


namespace Ui {
class GpsPage;
}

class GpsPage : public QWidget
{
    Q_OBJECT

public:
    explicit GpsPage(gui::PageController* controller, QWidget *parent = 0);
    ~GpsPage();

    void initialize();

signals:
    void signalBackPage();

private slots:
    void acquireGpsData();

private:
    void setupPage();
    void initializeSharedMemory();
    void initializeButtons(std::map<peripherals::SwitchCode, std::string> name, std::map<peripherals::SwitchCode, std::function<void()> > callbackFunctions);

    void firstButton();
    void secondButton();
    void thirdButton();
    void fourthButton();

    void startAcqTimer();
    void stopAcqTimer();
    void handleGpsData(const GPSData &measurements);

    config::UISharedMemory uiSharedMemoryParameters_;

    QTimer acqTimer_;
    std::unique_ptr<communication::SharedMemoryWrapper> sharedMemory_;

    Ui::GpsPage *ui_;
    gui::PageController* controller_;
    std::unique_ptr<Buttons> buttons_;

    utility::Logger& logger_;
};

#endif
