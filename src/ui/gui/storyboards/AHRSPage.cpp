#include <config_reader/ConfigurationReader.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>
#include <interfaces/wireless_measurement_commands/FeederData.h>
#include <interfaces/wireless_commands/StopAcqCommand.h>
#include <interfaces/wireless_commands/StartAcquisitionCommand.h>
#include <interfaces/gui/GUIWirelessComWrapperResponse.h>
#include <interfaces/gui/GUIStopAcqResponse.h>
#include <time_manager/TimeManager.h>

#include "AHRSPage.h"
#include "ui_AHRSPage.h"

using namespace std;
using namespace utility;
using namespace peripherals;
using namespace config;
using namespace communication;
using namespace boost::interprocess;

AHRSPage::AHRSPage(gui::PageController *controller, QWidget *parent)
        :   QWidget(parent),
            uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH)),
            controller_(controller),
            roll_0(0.0),
            roll(0.0),
            pitch_0(0.0),
            pitch(0.0),
            ui_(new Ui::AHRSPage),
            logger_(Logger::getInstance())
{
    ui_->setupUi(this);

    setup();
    initializeSharedMemory();
    startAcqTimer();
}

AHRSPage::~AHRSPage()
{
    if(ui_)
    {
        delete ui_;
    }

    stopAcqTimer();

    StopAcqCommand command;
    GUIWirelessComWrapperResponse response(UICommunicationMode::MASTER, command.getFrameBytes());
    controller_->sendToMainProcess(response.getFrameBytes());

    GUIStopAcqResponse stopAcq;
    controller_->sendToMainProcess(stopAcq.getFrameBytes());
}

void AHRSPage::setup()
{
    // SETUP avionic devices
    this->setStyleSheet("background-color:black;");

    widgetPFD_ = unique_ptr<WidgetPFD>(new WidgetPFD());
    ui_->pfdLayout->addWidget(widgetPFD_.get());

    widgetTC_ = unique_ptr<WidgetTC>(new WidgetTC());
    ui_->devicesLayout->addWidget(widgetTC_.get());

    widgetVSI_ = unique_ptr<WidgetVSI>(new WidgetVSI());
    widgetVSI_->setClimbRate(10.0);
    ui_->devicesLayout->addWidget(widgetVSI_.get());

    // SETUP top labels
    QFont upFont("Arial", 10, QFont::Bold);
    QFont downFont("Arial", 13, QFont::Bold);

    ui_->upFirstAHRS->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui_->upFirstAHRS->setFont(upFont);
    ui_->upFirstAHRS->setText("AHRS I");
    ui_->downFirstAHRS->setStyleSheet("QLabel {color : black; background-color: rgb(51,255,0)}");
    ui_->downFirstAHRS->setFont(downFont);
    ui_->downFirstAHRS->setText("MASTER");

    ui_->upSecondAHRS->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui_->upSecondAHRS->setFont(upFont);
    ui_->upSecondAHRS->setText("AHRS II");
    ui_->downSecondAHRS->setStyleSheet("QLabel {color : black; background-color: rgb(51,255,0)}");
    ui_->downSecondAHRS->setFont(downFont);
    ui_->downSecondAHRS->setText("REDUNDANT");

    ui_->upGrdSpeed->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui_->upGrdSpeed->setFont(upFont);
    ui_->upGrdSpeed->setText("GRD SPEED");
    ui_->downGrdSpeed->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui_->downGrdSpeed->setFont(downFont);
    ui_->downGrdSpeed->setText("0 kts");

    ui_->upAltGps->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui_->upAltGps->setFont(upFont);
    ui_->upAltGps->setText("ALT (GPS)");
    ui_->downAltGps->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui_->downAltGps->setFont(downFont);
    ui_->downAltGps->setText("0 ft");

    ui_->upFltDuration->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui_->upFltDuration->setFont(upFont);
    ui_->upFltDuration->setText("FLIGHT DURATION");
    ui_->downFltDuration->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui_->downFltDuration->setFont(downFont);
    ui_->downFltDuration->setText("00:00:00");

    ui_->upBoxPower->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui_->upBoxPower->setFont(upFont);
    ui_->upBoxPower->setText("FEEDER POWER");
    ui_->downBoxPower->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui_->downBoxPower->setFont(downFont);
    ui_->downBoxPower->setText("100 %");

    ui_->upPowerSupply->setStyleSheet("QLabel {color : white; background-color: rgb(45,45, 45)}");
    ui_->upPowerSupply->setFont(upFont);
    ui_->upPowerSupply->setText("POWER");
    ui_->downPowerSupply->setStyleSheet("QLabel {color : rgb(51,255,0); background-color: rgb(75, 75, 75)}");
    ui_->downPowerSupply->setFont(downFont);
    ui_->downPowerSupply->setText("100 %");
}

void AHRSPage::initializeSharedMemory()
{
    try
    {
        sharedMemory_ = unique_ptr<SharedMemoryWrapper>(new SharedMemoryWrapper(uiSharedMemoryParameters_.sharedMemoryName));
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("AHRSPage :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void AHRSPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "CALIBRATE";
    buttonNames[SwitchCode::SECOND_SWITCH] = "GPS";
    buttonNames[SwitchCode::THIRD_SWITCH] = "MENU";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "EXIT";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&AHRSPage::calibrateButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&AHRSPage::gpsButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&AHRSPage::menuButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&AHRSPage::exitButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalEXITPage()), controller_, SLOT(setExitPage()));
    QObject::connect(this, SIGNAL(signalGPSPage()), controller_, SLOT(setGpsPage()));
    QObject::connect(this, SIGNAL(signalMENUPage()), controller_, SLOT(setMenuPage()));
}

void AHRSPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = unique_ptr<Buttons>(new Buttons(this));
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void AHRSPage::calibrateButton()
{
    pitch_0 = pitch.load();
    roll_0 = roll.load();
}

void AHRSPage::menuButton()
{
    stopAcqTimer();
    QTimer::singleShot(50, this, SLOT(changeONMainPage()));
}

void AHRSPage::changeONMainPage()
{
    emit signalMENUPage();
}

void AHRSPage::gpsButton()
{
    stopAcqTimer();
    QTimer::singleShot(50, this, SLOT(changeONGpsPage()));
}

void AHRSPage::changeONGpsPage()
{
    emit signalGPSPage();
}

void AHRSPage::exitButton()
{
    stopAcqTimer();
    QTimer::singleShot(50, this, SLOT(changeONExitPage()));
}

void AHRSPage::changeONExitPage()
{
    emit signalEXITPage();
}

void AHRSPage::setRoll( float roll )
{
    widgetPFD_->setRoll( roll );
}

void AHRSPage::setPitch( float pitch )
{
    widgetPFD_->setPitch( pitch );
}

void AHRSPage::setAltitude( float altitude )
{
    string value = to_string(static_cast<uint32_t >(altitude)) + string(" ft");
    ui_->downAltGps->setText(value.c_str());
    widgetPFD_->setAltitude( altitude );
}

void AHRSPage::setPressure( float pressure )
{
    widgetPFD_->setPressure( pressure);
}

void AHRSPage::setAirspeed( float airspeed )
{
    string value = to_string(static_cast<uint32_t >(airspeed)) + string(" kts");
    ui_->downGrdSpeed->setText(value.c_str());
    widgetPFD_->setAirspeed( airspeed );
}

void AHRSPage::setMachNo( float machNo )
{
    widgetPFD_->setMachNo( machNo );
}

void AHRSPage::setHeading( float heading )
{
    widgetPFD_->setHeading( heading );
}

void AHRSPage::setClimbRate( float climbRate )
{
    widgetPFD_->setClimbRate( climbRate );
    widgetVSI_->setClimbRate( climbRate * 100 );
}

void AHRSPage::setTurnRate( float turnRate )
{
    widgetTC_->setTurnRate( turnRate );
}

void AHRSPage::setSlipSkid( float slipSkid )
{
    widgetTC_->setSlipSkid( slipSkid );
}

void AHRSPage::setTimeSinceStart(std::string time)
{
    ui_->downFltDuration->setText(time.c_str());
}

void AHRSPage::update()
{
    widgetTC_->update();
    widgetPFD_->update();
    widgetVSI_->update();
}

void AHRSPage::acquireFlightData()
{
    communication::MeasuringDataFactory dataFactory_;

    try
    {
        const auto  frame = sharedMemory_->read();

        if(frame.size() != 0)
        {
            auto flightData = static_pointer_cast<communication::FeederData, communication::MeasuringData>(
                    dataFactory_.createCommand(frame));

            const auto measurements = flightData->getMeasurements();
            handleFlightDataCommand(measurements.flightMeasurements);
        }
    }
    catch (exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-GUI- AHRSPage :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void AHRSPage::handleFlightDataCommand(const FlightMeasurements& measurements)
{
    float tempPitch, tempRoll;
    pitch = measurements.pitch;
    roll = measurements.roll;


    tempPitch = pitch - pitch_0;
    tempRoll = roll - roll_0;

    setRoll(tempRoll);
    setPitch(tempPitch);
    setHeading(measurements.heading);
    setSlipSkid(measurements.slipSkid);
    setTurnRate(measurements.turnCoordinator);
    setAirspeed(measurements.groundSpeed);
    setAltitude(measurements.altitude);
    setPressure(measurements.pressure);
    setClimbRate(measurements.verticalSpeed);
    setMachNo(measurements.machNo);
    setTimeSinceStart(TimeManager::getTimeSinceStart());
    update();
}

void AHRSPage::startAcqTimer()
{
    connect(&acqTimer_, SIGNAL(timeout()), this, SLOT(acquireFlightData()));
    acqTimer_.start(20);
}

void AHRSPage::stopAcqTimer()
{
    while(acqTimer_.isActive())
    {
        acqTimer_.stop();
    }
}
