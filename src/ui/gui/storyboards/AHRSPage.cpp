#include <config_reader/ConfigurationReader.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>
#include <interfaces/wireless_measurement_commands/FlightData.h>
#include "AHRSPage.h"
#include "ui_AHRSPage.h"

using namespace std;
using namespace utility;
using namespace peripherals;
using namespace config;
using namespace boost::interprocess;

AHRSPage::AHRSPage(gui::PageController *controller, QWidget *parent)
    :   QWidget(parent),
        uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH)),
        runAcquisitionThread_(false),
        controller_(controller),
        ui_(new Ui::AHRSPage),
        logger_(Logger::getInstance())
{
    ui_->setupUi(this);

    setup();

    initializeSharedMemory();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(acquireFlightData()));
    m_timer.start(100);
}

AHRSPage::~AHRSPage()
{
    if(ui_)
    {
        delete ui_;
    }

    m_timer.stop();
}

void AHRSPage::setup()
{
    // SETUP avionic devices
    this->setStyleSheet("background-color:black;");

    widgetPFD_ = make_unique<WidgetPFD>();
    ui_->pfdLayout->addWidget(widgetPFD_.get());

    widgetTC_ = make_unique<WidgetTC>();
    ui_->devicesLayout->addWidget(widgetTC_.get());

    widgetVSI_ = make_unique<WidgetVSI>();
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
        // Creating shared memory's mutex.
        sharedMemoryMutex_ = make_unique<named_mutex>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str());
        // Creating shared memory.
        sharedMemory_ = make_unique<shared_memory_object>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str(), read_write);
        // Mapped shared memory.
        mappedMemoryRegion_ = make_unique<mapped_region>(*sharedMemory_, read_write);
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
    buttonNames[SwitchCode::SECOND_SWITCH] = "LOGS";
    buttonNames[SwitchCode::THIRD_SWITCH] = "MENU";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "EXIT";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&AHRSPage::calibrateButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&AHRSPage::logsButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&AHRSPage::menuButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&AHRSPage::exitButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalEXITPage()), controller_, SLOT(setExitPage()));
    QObject::connect(this, SIGNAL(signalLOGSPage()), controller_, SLOT(setLogsPage()));
    QObject::connect(this, SIGNAL(signalMENUPage()), controller_, SLOT(setMenuPage()));
}

void AHRSPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>();
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void AHRSPage::calibrateButton()
{
    ///TBD
}

void AHRSPage::menuButton()
{
    emit signalMENUPage();
}

void AHRSPage::logsButton()
{
    emit signalLOGSPage();
}

void AHRSPage::exitButton()
{
    emit signalEXITPage();
}

void AHRSPage::setRoll( float roll )
{
    widgetPFD_->setRoll( roll );
    widgetPFD_->update();
}

void AHRSPage::setPitch( float pitch )
{
    widgetPFD_->setPitch( pitch );
    widgetPFD_->update();
}

void AHRSPage::setAltitude( float altitude )
{
    widgetPFD_->setAltitude( altitude );
    widgetPFD_->update();
}

void AHRSPage::setPressure( float pressure )
{
    widgetPFD_->setPressure( pressure);
    widgetPFD_->update();
}

void AHRSPage::setAirspeed( float airspeed )
{
    widgetPFD_->setAirspeed( airspeed );
    widgetPFD_->update();
}

void AHRSPage::setMachNo( float machNo )
{
    widgetPFD_->setMachNo( machNo );
    widgetPFD_->update();
}

void AHRSPage::setHeading( float heading )
{
    widgetPFD_->setHeading( heading );
    widgetPFD_->update();
}

void AHRSPage::setClimbRate( float climbRate )
{
    widgetPFD_->setClimbRate( climbRate );
    widgetPFD_->update();

    widgetVSI_->setClimbRate( climbRate );
    widgetVSI_->update();
}

void AHRSPage::setTurnRate( float turnRate )
{
    widgetTC_->setTurnRate( turnRate );
    widgetTC_->update();
}

void AHRSPage::setSlipSkid( float slipSkid )
{
    widgetTC_->setSlipSkid( slipSkid );
    widgetTC_->update();
}

void AHRSPage::acquireFlightData()
{
    communication::MeasuringDataFactory dataFactory_;

    vector<uint8_t> frame;
    frame.resize(mappedMemoryRegion_->get_size());

    uint8_t *memory = nullptr;
    {
        scoped_lock<named_mutex> lock(*sharedMemoryMutex_.get());
        memory = reinterpret_cast<uint8_t* >(mappedMemoryRegion_->get_address());
        memcpy(frame.data(), memory, mappedMemoryRegion_->get_size());
    }

    if(frame.size() != 0)
    {
        auto flightData = static_pointer_cast<communication::FlightData, communication::MeasuringData>(
                dataFactory_.createCommand(frame));

        handleFlightDataCommand(flightData->getMeasurements());

        if ( logger_.isInformationEnable())
        {
            const string message =
                    string("AHRSPage:: ") + flightData->getName() +
                    string(" Altitude: ") + to_string(flightData->getMeasurements().altitude)+
                    string(" roll: ") + to_string(flightData->getMeasurements().roll) +
                    string(" verticalSpeed: ") + to_string(flightData->getMeasurements().verticalSpeed) +
                    string(" groundSpeed: ") + to_string(flightData->getMeasurements().groundSpeed) +
                    string(" turnCoordinator: ") + to_string(flightData->getMeasurements().turnCoordinator) +
                    string(" heading: ") + to_string(flightData->getMeasurements().heading) +
                    string(" machNo: ") + to_string(flightData->getMeasurements().machNo) +
                    string(" latitude: ") + to_string(flightData->getMeasurements().latitude) +
                    string(" pitch: ") + to_string(flightData->getMeasurements().pitch) +
                    string(" pressure: ") + to_string(flightData->getMeasurements().pressure);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
}

void AHRSPage::handleFlightDataCommand(const FlightMeasurements& measurements)
{
    widgetVSI_->setClimbRate(2345.90);
    widgetVSI_->update();
    setRoll(measurements.roll);
    setPitch(measurements.pitch);
    setHeading(measurements.heading);
    setSlipSkid(measurements.slipSkid);
    setTurnRate(measurements.turnCoordinator);
    setAirspeed(measurements.groundSpeed);
    setAltitude(measurements.altitude);
    setPressure(measurements.pressure);
    setClimbRate(measurements.verticalSpeed);
    setMachNo(measurements.machNo);
}
