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
#include <config_reader/UIParameters.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

#include "MainWindow.h"
#include "GUIDataManager.h"
#include "PageController.h"
#include "storyboards/ExitPage.h"
#include "storyboards/AHRSPage.h"
#include "storyboards/LogsPage.h"
#include "storyboards/MainPage.h"
#include "storyboards/WelcomePage.h"
#include "storyboards/SystemSetupPage.h"
#include "storyboards/PlaneSettingsPage.h"
#include "storyboards/RestartPage.h"
#include "storyboards/InformationPage.h"
#include "storyboards/ConnectingPage.h"
#include "storyboards/CallibrationPage.h"

#include <../../common/UIStates.h>


class StoryboardsHandler final : public gui::PageController
{
    Q_OBJECT
public:
    StoryboardsHandler();

    void setupUi(QMainWindow *MainWindow);

public slots:
    void sendToMainProcess(std::vector<uint8_t> msg);
    void backToPreviousPage() override;
    void setWelcomePage() override;
    void setSystemSetupPage() override;
    void setPlaneSettingPage() override;
    void setRestartPage() override;
    void setExitPage() override;
    void setAHRSPage() override;
    void setLogsPage() override;
    void setMenuPage() override;
    void setConnectingPage() override;
    void setCallibrationPage() override;
    void setBITSPage() override;

    void setPlaneName(const std::string& name) override;
    const std::string& getPlaneName() override;

    void setPlaneDataset(const std::string& name) override;
    const std::string& getPlaneDataset() override;

    void setMainCallibrationParameters(const communication::CalibrationConfiguration& paramteres) override;
    void setRedundantCallibrationParameters(const communication::CalibrationConfiguration& paramteres) override;

    const communication::CalibrationConfiguration& getMainCallibrationParameters() override;
    const communication::CalibrationConfiguration& getRedundantCallibrationParameters() override;

    void setBitsInformation(uint8_t master, uint8_t redundant, uint8_t masterBITs, uint8_t redundantBITs) override;
    std::tuple<uint8_t , uint8_t , uint8_t, uint8_t> getBitsInformation() override;

    bool isSystemActive() override;
    void setSystemActivation() override;

    bool areBITSActive();
    void setBITSActive();

private:

    void inititalizeMessageQueue();
    void initializeStoryboardsContainer();

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
    PlaneSettingsPage* planeSettings_;
    InformationPage* bitsPage_;
    ConnectingPage* connectingPage_;
    CallibrationPage* callibrationPage_;

    QWidget *previousWidget_;

    gui::GUIDataManager guiDataManager_;

    config::UIMessageQueues uiMessageQueuesParameters_;
    std::unique_ptr<communication::MessageQueueWrapper> sendingMessageQueue_;

    PagesType previousPage_;
    PagesType currentPage_;
    std::map<PagesType, std::function<void()> > storyboardsContainer_;

    utility::Logger& logger_;
};

#endif
