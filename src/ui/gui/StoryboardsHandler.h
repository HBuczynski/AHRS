#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

#include <memory>
#include <tuple>
#include <atomic>
#include <config_reader/UIParameters.h>
#include <boost/interprocess/ipc/message_queue.hpp>

#include "MainWindow.h"
#include "PageController.h"
#include "storyboards/ExitPage.h"
#include "storyboards/AHRSPage.h"
#include "storyboards/LogsPage.h"
#include "storyboards/MainPage.h"
#include "storyboards/WelcomePage.h"
#include "storyboards/SystemSetupPage.h"
#include "storyboards/CallibrationSettings.h"
#include "storyboards/RestartPage.h"
#include "storyboards/InformationPage.h"
#include "storyboards/ConnectingPage.h"

#include <../../common/UIStates.h>


class StoryboardsHandler final : public gui::PageController
{
    Q_OBJECT
public:
    StoryboardsHandler();
    ~StoryboardsHandler();

    void setupUi(QMainWindow *MainWindow);

public slots:
    void sendToMainProcess(std::vector<uint8_t> msg);
    void backToPreviousPage() override;
    void setWelcomePage() override;
    void setSystemSetupPage() override;
    void setCallibrationSettingPage() override;
    void setRestartPage() override;
    void setExitPage() override;
    void setAHRSPage() override;
    void setLogsPage() override;
    void setMenuPage() override;
    void setConnectingPage() override;
    void setInformationPage(uint8_t master, uint8_t redundant, uint8_t masterBITs, uint8_t redundantBITs) override;

    void acquireFlightData();

private:
    void stopTimer();
    void inititalizeMessageQueue();
    void initializeSharedMemory();
    void initializeStoryboardsContainer();

    void handleFlightDataCommand(const FlightMeasurements& measurements);
    config::UISharedMemory uiSharedMemoryParameters_;

    QTimer acqTimer_;
    std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
    std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
    std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

    std::unique_ptr<QWidget> centralWidget;
    std::unique_ptr<QGridLayout> gridLayout_5;
    std::unique_ptr<QSplitter> splitter;
    std::unique_ptr<QFrame> frame_2;
    std::unique_ptr<QGridLayout> gridLayout_4;
    std::unique_ptr<QGridLayout> gridLayout_2;

    AHRSPage* ahrsPage_;
    ExitPage* exitPage_;
    LogsPage* logsPage_;
    MainPage* mainPage_;
    RestartPage* restartPage_;
    WelcomePage* welcomePage_;
    SystemSetupPage* systemSetupPage_;
    CallibrationSettings* calibrationSettings_;
    InformationPage* informationPage_;
    ConnectingPage* connectingPage_;

    QWidget *previousWidget_;

    config::UIMessageQueues uiMessageQueuesParameters_;
    std::unique_ptr<boost::interprocess::message_queue> sendingMessageQueue_;

    std::atomic<PagesType> previousPage_;
    std::atomic<PagesType> currentPage_;
    std::map<PagesType, std::function<void()> > storyboardsContainer_;
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> informationsParameters_;

    utility::Logger& logger_;
};

#endif
