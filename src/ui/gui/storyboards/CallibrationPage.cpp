#include "CallibrationPage.h"
#include "ui_CallibrationPage.h"

#include <interfaces/wireless_commands/CalibrateAccelerometerCommand.h>
#include <interfaces/wireless_commands/CallibrateMagnetometerCommand.h>
#include <interfaces/wireless_commands/PerformBITsCommand.h>
#include <interfaces/wireless_commands/CalibrateDataCommand.h>
#include <interfaces/gui/GUIWirelessComWrapperResponse.h>
#include <interfaces/gui/GUIWindowResponse.h>

#define FIRST_STEP 0x01
#define SECOND_STEP 0x02
#define THIRD_STEP 0x04

using namespace std;
using namespace communication;
using namespace peripherals;

CallibrationPage::CallibrationPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    mode_(1),
    currentMode_(CalibrationMode::IDLE),
    ui_(new Ui::CallibrationPage),
    controller_(controller)
{
    ui_->setupUi(this);
    setupPage(mode_);
    timerInterrupt_.startPeriodic(USER_UPDATE_INTERVAL_MS, this);
}

CallibrationPage::~CallibrationPage()
{
    timerInterrupt_.stop();
    delete ui_;
}

void CallibrationPage::interruptNotification(timer_t timerID)
{
    CalibrateDataCommand calibrateDataCommand;
    GUIWirelessComWrapperResponse response2(calibrateDataCommand.getFrameBytes());
    controller_->sendToMainProcess(response2.getFrameBytes());
}

void CallibrationPage::setupPage(uint8_t mode)
{
    mode_ = mode;

    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    if(mode_)
    {
        currentConfiguration_ = controller_->getMainCallibrationParameters();
        setupMaster();
    }
    else
    {
        currentConfiguration_ = controller_->getRedundantCallibrationParameters();
        setupRedundant();
    }

    //TODO: Update after redundant state.
    if(currentConfiguration_.status == CalibrationStatus::IS_CALIBRATED)
    {
        controller_->setBITSActive();
        timerInterrupt_.stop();
    }
}

void CallibrationPage::setupMaster()
{
    QFont font("Arial", 30, QFont::Bold);
    QFont fontSmaller("Arial", 20, QFont::Bold);
    QFont fontTheSmallest("Arial", 15, QFont::Bold);

    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("CALLIBRATION - MASTER");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    ui_->master_leftLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->master_leftLabel->setFont(fontSmaller);
    ui_->master_leftLabel->setText("MASTER STATUS");
    ui_->master_leftLabel->setAlignment(Qt::AlignLeft);

    ui_->master_centerLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->master_centerLabel->setFont(fontTheSmallest);
    ui_->master_centerLabel->setText("..............................................................................................................................");
    ui_->master_centerLabel->setAlignment(Qt::AlignCenter);

    ui_->master_rightLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->master_rightLabel->setFont(fontSmaller);
    ui_->master_rightLabel->setText(getCallibrationStatus(controller_->getMainCallibrationParameters().status).c_str());
    ui_->master_rightLabel->setAlignment(Qt::AlignRight);

    ui_->redundant_leftLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");
    ui_->redundant_leftLabel->setFont(fontSmaller);
    ui_->redundant_leftLabel->setText("REDUNDANT STATUS");
    ui_->redundant_leftLabel->setAlignment(Qt::AlignLeft);

    ui_->redundant_centerLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");
    ui_->redundant_centerLabel->setFont(fontTheSmallest);
    ui_->redundant_centerLabel->setText("..............................................................................................................................");
    ui_->redundant_centerLabel->setAlignment(Qt::AlignCenter);

    ui_->redundant_rightLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");
    ui_->redundant_rightLabel->setFont(fontSmaller);
    ui_->redundant_rightLabel->setText(getCallibrationStatus(controller_->getRedundantCallibrationParameters().status).c_str());
    ui_->redundant_rightLabel->setAlignment(Qt::AlignRight);

    ui_->noteLabel->setStyleSheet("QLabel { color: rgb(250,0,0)}");
    ui_->noteLabel->setFont(fontTheSmallest);
    ui_->noteLabel->setText(" ");
    ui_->noteLabel->setAlignment(Qt::AlignLeft);

    startCallibartion();
}

void CallibrationPage::setupRedundant()
{
    QFont font("Arial", 30, QFont::Bold);
    QFont fontSmaller("Arial", 20, QFont::Bold);
    QFont fontTheSmallest("Arial", 15, QFont::Bold);

    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("CALLIBRATION - REDUNDANT");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    ui_->master_leftLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");
    ui_->master_leftLabel->setFont(fontSmaller);
    ui_->master_leftLabel->setText("MASTER STATUS");
    ui_->master_leftLabel->setAlignment(Qt::AlignLeft);

    ui_->master_centerLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");;
    ui_->master_centerLabel->setFont(fontTheSmallest);
    ui_->master_centerLabel->setText("..............................................................................................................................");
    ui_->master_centerLabel->setAlignment(Qt::AlignCenter);

    ui_->master_rightLabel->setStyleSheet("QLabel { color: rgb(105,105, 105)}");
    ui_->master_rightLabel->setFont(fontSmaller);
    ui_->master_rightLabel->setText(getCallibrationStatus(controller_->getMainCallibrationParameters().status).c_str());
    ui_->master_rightLabel->setAlignment(Qt::AlignRight);

    ui_->redundant_leftLabel->setStyleSheet("QLabel { color: rgb(250, 250, 250)}");
    ui_->redundant_leftLabel->setFont(fontSmaller);
    ui_->redundant_leftLabel->setText("REDUNDANT STATUS");
    ui_->redundant_leftLabel->setAlignment(Qt::AlignLeft);

    ui_->redundant_centerLabel->setStyleSheet("QLabel { color: rgb(250, 250, 250)}");
    ui_->redundant_centerLabel->setFont(fontTheSmallest);
    ui_->redundant_centerLabel->setText("..............................................................................................................................");
    ui_->redundant_centerLabel->setAlignment(Qt::AlignCenter);

    ui_->redundant_rightLabel->setStyleSheet("QLabel { color: rgb(250, 250, 250)}");
    ui_->redundant_rightLabel->setFont(fontSmaller);
    ui_->redundant_rightLabel->setText(getCallibrationStatus(controller_->getRedundantCallibrationParameters().status).c_str());
    ui_->redundant_rightLabel->setAlignment(Qt::AlignRight);

    ui_->noteLabel->setStyleSheet("QLabel { color: rgb(250,0,0)}");
    ui_->noteLabel->setFont(fontTheSmallest);
    ui_->noteLabel->setText(" ");
    ui_->noteLabel->setAlignment(Qt::AlignLeft);

    startCallibartion();
}

void CallibrationPage::startCallibartion()
{
    if(currentConfiguration_.progress & FIRST_STEP)
    {
        setAccelerometerParameters();

        if(currentConfiguration_.progress & SECOND_STEP)
        {
            setMagnetometerParameters();

            if(currentConfiguration_.progress & THIRD_STEP)
            {
                setEllipsoidParameters();
                calibrateElipsoid();
            }
            else
            {
                // ellipsoid's callibration
                setEllipsoidParameters();
                calibrateElipsoid();
            }
        }
        else
        {
            // magnetometer's callibration
            setMagnetometerParameters();
            calibrateMagnetometer();
        }
    }
    else
    {
        // accelerometer's callibration
        setAccelerometerParameters();
        calibrateAccelerometer();
    }
}

void CallibrationPage::setAccelerometerParameters()
{
    QFont fontTheSmallest("Arial", 15, QFont::Bold);

    ui_->mAccelLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->mAccelLabel->setFont(fontTheSmallest);
    ui_->mAccelLabel->setText("ACCELEROMETER");
    ui_->mAccelLabel->setAlignment(Qt::AlignLeft);

    ui_->mMinLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->mMinLabel->setFont(fontTheSmallest);
    ui_->mMinLabel->setText("MIN:");
    ui_->mMinLabel->setAlignment(Qt::AlignLeft);

    ui_->mXLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mXLabelMin->setFont(fontTheSmallest);
    ui_->mXLabelMin->setText("X:");
    ui_->mXLabelMin->setAlignment(Qt::AlignLeft);

    ui_->mXValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mXValueMin->setFont(fontTheSmallest);
    ui_->mXValueMin->setText(to_string(currentConfiguration_.accelerometer.minX).c_str());
    ui_->mXValueMin->setAlignment(Qt::AlignLeft);

    ui_->mYLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYLabelMin->setFont(fontTheSmallest);
    ui_->mYLabelMin->setText("Y:");
    ui_->mYLabelMin->setAlignment(Qt::AlignLeft);

    ui_->mYValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYValueMin->setFont(fontTheSmallest);
    ui_->mYValueMin->setText(to_string(currentConfiguration_.accelerometer.minY).c_str());
    ui_->mYValueMin->setAlignment(Qt::AlignLeft);

    ui_->mZLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZLabelMin->setFont(fontTheSmallest);
    ui_->mZLabelMin->setText("Z:");
    ui_->mZLabelMin->setAlignment(Qt::AlignLeft);

    ui_->mZValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZValueMin->setFont(fontTheSmallest);
    ui_->mZValueMin->setText(to_string(currentConfiguration_.accelerometer.minZ).c_str());
    ui_->mZValueMin->setAlignment(Qt::AlignLeft);

    ui_->mMaxLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->mMaxLabel->setFont(fontTheSmallest);
    ui_->mMaxLabel->setText("MAX:");
    ui_->mMaxLabel->setAlignment(Qt::AlignLeft);

    ui_->mXLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mXLabelMax->setFont(fontTheSmallest);
    ui_->mXLabelMax->setText("X:");
    ui_->mXLabelMax->setAlignment(Qt::AlignLeft);

    ui_->mXValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mXValueMax->setFont(fontTheSmallest);
    ui_->mXValueMax->setText(to_string(currentConfiguration_.accelerometer.maxX).c_str());
    ui_->mXValueMax->setAlignment(Qt::AlignLeft);

    ui_->mYLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYLabelMax->setFont(fontTheSmallest);
    ui_->mYLabelMax->setText("Y:");
    ui_->mYLabelMax->setAlignment(Qt::AlignLeft);

    ui_->mYValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYValueMax->setFont(fontTheSmallest);
    ui_->mYValueMax->setText(to_string(currentConfiguration_.accelerometer.maxY).c_str());
    ui_->mYValueMax->setAlignment(Qt::AlignLeft);

    ui_->mZLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZLabelMax->setFont(fontTheSmallest);
    ui_->mZLabelMax->setText("Z:");
    ui_->mZLabelMax->setAlignment(Qt::AlignLeft);

    ui_->mZValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZValueMax->setFont(fontTheSmallest);
    ui_->mZValueMax->setText(to_string(currentConfiguration_.accelerometer.maxZ).c_str());
    ui_->mZValueMax->setAlignment(Qt::AlignLeft);
}

void CallibrationPage::calibrateAccelerometer()
{
    if(currentConfiguration_.accelerometer.mode == 1)
    {
        string text = "Note: Axis - " + getAxisName(currentConfiguration_.accelerometer.axis) + " is enabled.";
        if(currentConfiguration_.accelerometer.approved)
            text += string(" Approved.");

        currentMode_ = CalibrationMode::ACCEL_ENABLE;
        ui_->noteLabel->setText(text.c_str());
    }
    else
    {
        string text = "Note: Axis - " + getAxisName(currentConfiguration_.accelerometer.axis) + " is disbaled.";
        if(currentConfiguration_.accelerometer.approved)
            text += string(" Approved.");

        currentMode_ = CalibrationMode::ACCEL_DISABLE;
        ui_->noteLabel->setText(text.c_str());
    }

    initialize();
}

void CallibrationPage::setMagnetometerParameters()
{
    QFont fontTheSmallest("Arial", 15, QFont::Bold);

    ui_->magnetometerLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->magnetometerLabel->setFont(fontTheSmallest);
    ui_->magnetometerLabel->setText("MAGNETOMETER");
    ui_->magnetometerLabel->setAlignment(Qt::AlignLeft);

    ui_->magMinLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->magMinLabel->setFont(fontTheSmallest);
    ui_->magMinLabel->setText("MIN:");
    ui_->magMinLabel->setAlignment(Qt::AlignLeft);

    ui_->magXLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magXLabelMin->setFont(fontTheSmallest);
    ui_->magXLabelMin->setText("X:");
    ui_->magXLabelMin->setAlignment(Qt::AlignLeft);

    ui_->magXValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magXValueMin->setFont(fontTheSmallest);
    ui_->magXValueMin->setText(to_string(currentConfiguration_.magnetometer.minX).c_str());
    ui_->magXValueMin->setAlignment(Qt::AlignLeft);

    ui_->magYLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYLabelMin->setFont(fontTheSmallest);
    ui_->magYLabelMin->setText("Y:");
    ui_->magYLabelMin->setAlignment(Qt::AlignLeft);

    ui_->magYValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYValueMin->setFont(fontTheSmallest);
    ui_->magYValueMin->setText(to_string(currentConfiguration_.magnetometer.minY).c_str());
    ui_->magYValueMin->setAlignment(Qt::AlignLeft);

    ui_->magZLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZLabelMin->setFont(fontTheSmallest);
    ui_->magZLabelMin->setText("Z:");
    ui_->magZLabelMin->setAlignment(Qt::AlignLeft);

    ui_->magZValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZValueMin->setFont(fontTheSmallest);
    ui_->magZValueMin->setText(to_string(currentConfiguration_.magnetometer.minZ).c_str());
    ui_->magZValueMin->setAlignment(Qt::AlignLeft);

    ui_->magMaxLabel->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->magMaxLabel->setFont(fontTheSmallest);
    ui_->magMaxLabel->setText("MAX:");
    ui_->magMaxLabel->setAlignment(Qt::AlignLeft);

    ui_->magXLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magXLabelMax->setFont(fontTheSmallest);
    ui_->magXLabelMax->setText("X:");
    ui_->magXLabelMax->setAlignment(Qt::AlignLeft);

    ui_->magXValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magXValueMax->setFont(fontTheSmallest);
    ui_->magXValueMax->setText(to_string(currentConfiguration_.magnetometer.maxX).c_str());
    ui_->magXValueMax->setAlignment(Qt::AlignLeft);

    ui_->magYLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYLabelMax->setFont(fontTheSmallest);
    ui_->magYLabelMax->setText("Y:");
    ui_->magYLabelMax->setAlignment(Qt::AlignLeft);

    ui_->magYValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYValueMax->setFont(fontTheSmallest);
    ui_->magYValueMax->setText(to_string(currentConfiguration_.magnetometer.maxY).c_str());
    ui_->magYValueMax->setAlignment(Qt::AlignLeft);

    ui_->magZLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZLabelMax->setFont(fontTheSmallest);
    ui_->magZLabelMax->setText("Z:");
    ui_->magZLabelMax->setAlignment(Qt::AlignLeft);

    ui_->magZValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZValueMax->setFont(fontTheSmallest);
    ui_->magZValueMax->setText(to_string(currentConfiguration_.magnetometer.maxZ).c_str());
    ui_->magZValueMax->setAlignment(Qt::AlignLeft);
}

void CallibrationPage::calibrateMagnetometer()
{
    string text = "Note: Find min and max values in axes.";
    currentMode_ = CalibrationMode::MAGNETOMETER;
    ui_->noteLabel->setText(text.c_str());

    initialize();
}

void CallibrationPage:: setEllipsoidParameters()
{
    QFont fontTheSmallest("Arial", 15, QFont::Bold);

    string value;
    ui_->ellipsoidLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->ellipsoidLabel->setFont(fontTheSmallest);
    ui_->ellipsoidLabel->setText("ELLIPSOID");
    ui_->ellipsoidLabel->setAlignment(Qt::AlignLeft);

    ui_->elLabel_1->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->elLabel_1->setFont(fontTheSmallest);
    ui_->elLabel_1->setText("---:");
    ui_->elLabel_1->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_11) + string(" / 200");
    ui_->elValue_1->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_1->setFont(fontTheSmallest);
    ui_->elValue_1->setText(value.c_str());
    ui_->elValue_1->setAlignment(Qt::AlignLeft);

    ui_->elLabel_2->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_2->setFont(fontTheSmallest);
    ui_->elLabel_2->setText("+--:");
    ui_->elLabel_2->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_12) + string(" / 200");
    ui_->elValue_2->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_2->setFont(fontTheSmallest);
    ui_->elValue_2->setText(value.c_str());
    ui_->elValue_2->setAlignment(Qt::AlignLeft);

    ui_->elLabel_3->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_3->setFont(fontTheSmallest);
    ui_->elLabel_3->setText("-+-:");
    ui_->elLabel_3->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_13) + string(" / 200");
    ui_->elValue_3->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_3->setFont(fontTheSmallest);
    ui_->elValue_3->setText(value.c_str());
    ui_->elValue_3->setAlignment(Qt::AlignLeft);

    ui_->elLabel_4->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_4->setFont(fontTheSmallest);
    ui_->elLabel_4->setText("++-:");
    ui_->elLabel_4->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_21) + string(" / 200");
    ui_->elValue_4->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->elValue_4->setFont(fontTheSmallest);
    ui_->elValue_4->setText(value.c_str());
    ui_->elValue_4->setAlignment(Qt::AlignLeft);

    ui_->elLabel_5->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_5->setFont(fontTheSmallest);
    ui_->elLabel_5->setText("--+:");
    ui_->elLabel_5->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_22) + string(" / 200");
    ui_->elValue_5->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_5->setFont(fontTheSmallest);
    ui_->elValue_5->setText(value.c_str());
    ui_->elValue_5->setAlignment(Qt::AlignLeft);

    ui_->elLabel_6->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_6->setFont(fontTheSmallest);
    ui_->elLabel_6->setText("+-+:");
    ui_->elLabel_6->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_23) + string(" / 200");
    ui_->elValue_6->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_6->setFont(fontTheSmallest);
    ui_->elValue_6->setText(value.c_str());
    ui_->elValue_6->setAlignment(Qt::AlignLeft);

    ui_->elLabel_7->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_7->setFont(fontTheSmallest);
    ui_->elLabel_7->setText("-++:");
    ui_->elLabel_7->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_31) + string(" / 200");
    ui_->elValue_7->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_7->setFont(fontTheSmallest);
    ui_->elValue_7->setText(value.c_str());
    ui_->elValue_7->setAlignment(Qt::AlignLeft);

    ui_->elLabel_8->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_8->setFont(fontTheSmallest);
    ui_->elLabel_8->setText("+++:");
    ui_->elLabel_8->setAlignment(Qt::AlignLeft);

    value = to_string(currentConfiguration_.ellipsoid.quadrant_32) + string(" / 200");
    ui_->elValue_8->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_8->setFont(fontTheSmallest);
    ui_->elValue_8->setText(value.c_str());
    ui_->elValue_8->setAlignment(Qt::AlignLeft);


    //TODO new quadrant !!!!!!!!!!
}

void CallibrationPage::calibrateElipsoid()
{
    if(currentConfiguration_.ellipsoid.mode == 1)
    {
        string text = "Note: Finished Master calibration. Go to Redundant Calibration.";
        currentMode_ = CalibrationMode::ELLIPSOID_DONE;
        ui_->noteLabel->setText(text.c_str());
    }
    else
    {
        string text = "Note: Counts for each of the 8 poses is displayed.";
        currentMode_ = CalibrationMode::ELLIPSOID;
        ui_->noteLabel->setText(text.c_str());
    }

    initialize();
}

void CallibrationPage::initialize()
{
    const auto buttonNames = configureButtons();

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&CallibrationPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&CallibrationPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&CallibrationPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&CallibrationPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackPage()), controller_, SLOT(backToPreviousPage()));
    QObject::connect(this, SIGNAL(signalBITSPage()), controller_, SLOT(setBITSPage()));
}

map<SwitchCode, string> CallibrationPage::configureButtons()
{
    map<SwitchCode, string> buttonNames;

    switch (currentMode_)
    {
        case CalibrationMode::IDLE :
        {
            buttonNames[SwitchCode::FIRST_SWITCH] = " ";
            buttonNames[SwitchCode::SECOND_SWITCH] = " ";
            buttonNames[SwitchCode::THIRD_SWITCH] = " ";
            buttonNames[SwitchCode::FOURTH_SWITCH] = "< BACK";
            break;
        }
        case CalibrationMode::ACCEL_ENABLE :
        {
            buttonNames[SwitchCode::FIRST_SWITCH] = "< BACK";
            buttonNames[SwitchCode::SECOND_SWITCH] = "DISABLE";
            buttonNames[SwitchCode::THIRD_SWITCH] = "APPROVE";
            buttonNames[SwitchCode::FOURTH_SWITCH] = "NEXT AXIS";
            break;
        }
        case CalibrationMode::ACCEL_DISABLE :
        {
            buttonNames[SwitchCode::FIRST_SWITCH] = "< BACK";
            buttonNames[SwitchCode::SECOND_SWITCH] = "ENABLE";
            buttonNames[SwitchCode::THIRD_SWITCH] = "APPROVE";
            buttonNames[SwitchCode::FOURTH_SWITCH] = "NEXT AXIS";
            break;
        }
        case CalibrationMode::MAGNETOMETER :
        {
            buttonNames[SwitchCode::FIRST_SWITCH] = " ";
            buttonNames[SwitchCode::SECOND_SWITCH] = " ";
            buttonNames[SwitchCode::THIRD_SWITCH] = "< BACK";
            buttonNames[SwitchCode::FOURTH_SWITCH] = "APPROVE";
            break;
        }
        case CalibrationMode::ELLIPSOID :
        {
            buttonNames[SwitchCode::FIRST_SWITCH] = " ";
            buttonNames[SwitchCode::SECOND_SWITCH] = " ";
            buttonNames[SwitchCode::THIRD_SWITCH] = " ";
            buttonNames[SwitchCode::FOURTH_SWITCH] = "< BACK";
            break;
        }
        case CalibrationMode::ELLIPSOID_DONE :
        {
            if(mode_)
            {
                buttonNames[SwitchCode::FIRST_SWITCH] = " ";
                buttonNames[SwitchCode::SECOND_SWITCH] = " ";
                buttonNames[SwitchCode::THIRD_SWITCH] = "< BACK";
                buttonNames[SwitchCode::FOURTH_SWITCH] = "BITS";
            }
            else
            {
                buttonNames[SwitchCode::FIRST_SWITCH] = " ";
                buttonNames[SwitchCode::SECOND_SWITCH] = " ";
                buttonNames[SwitchCode::THIRD_SWITCH] = "< BACK";
                buttonNames[SwitchCode::FOURTH_SWITCH] = "BITS";
            }
            break;
        }
        default:
            break;
    }

    return buttonNames;
}

void CallibrationPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void CallibrationPage::firstButton()
{
    switch (currentMode_)
    {
        case CalibrationMode::IDLE :
            break;
        case CalibrationMode::ACCEL_ENABLE :
        case CalibrationMode::ACCEL_DISABLE :
            emit signalBackPage();
            break;
        case CalibrationMode::ELLIPSOID :
        case CalibrationMode::ELLIPSOID_DONE :
        case CalibrationMode::MAGNETOMETER :
        default:
            break;
    }
}

void CallibrationPage::secondButton()
{
    switch (currentMode_)
    {
        case CalibrationMode::IDLE :
        case CalibrationMode::ACCEL_ENABLE :
        {
            CalibrateAccelerometerCommand command(currentConfiguration_.accelerometer.axis, AccelAction::DISABLE);
            GUIWirelessComWrapperResponse response(command.getFrameBytes());
            controller_->sendToMainProcess(response.getFrameBytes());
            break;
        }
        case CalibrationMode::ACCEL_DISABLE :
        {
            CalibrateAccelerometerCommand command(currentConfiguration_.accelerometer.axis, AccelAction::ENABLE);
            GUIWirelessComWrapperResponse response(command.getFrameBytes());
            controller_->sendToMainProcess(response.getFrameBytes());

            this_thread::sleep_for(std::chrono::milliseconds(200));

            CalibrateDataCommand calibrateDataCommand;
            GUIWirelessComWrapperResponse response2(calibrateDataCommand.getFrameBytes());
            controller_->sendToMainProcess(response2.getFrameBytes());

            break;
        }
        case CalibrationMode::ELLIPSOID :
        case CalibrationMode::ELLIPSOID_DONE :
        case CalibrationMode::MAGNETOMETER :
        default:
            break;
    }
}

void CallibrationPage::thirdButton()
{
    switch (currentMode_)
    {
        case CalibrationMode::IDLE :
            break;
        case CalibrationMode::ACCEL_ENABLE :
        {
            CalibrateAccelerometerCommand command(currentConfiguration_.accelerometer.axis, AccelAction::APPROVE);
            GUIWirelessComWrapperResponse response(command.getFrameBytes());
            controller_->sendToMainProcess(response.getFrameBytes());

            this_thread::sleep_for(std::chrono::milliseconds(200));

            CalibrateDataCommand calibrateDataCommand;
            GUIWirelessComWrapperResponse response2(calibrateDataCommand.getFrameBytes());
            controller_->sendToMainProcess(response2.getFrameBytes());

            break;
        }
        case CalibrationMode::ACCEL_DISABLE :
        {
            CalibrateAccelerometerCommand command(currentConfiguration_.accelerometer.axis, AccelAction::APPROVE);
            GUIWirelessComWrapperResponse response(command.getFrameBytes());
            controller_->sendToMainProcess(response.getFrameBytes());

            this_thread::sleep_for(std::chrono::milliseconds(200));

            CalibrateDataCommand calibrateDataCommand;
            GUIWirelessComWrapperResponse response2(calibrateDataCommand.getFrameBytes());
            controller_->sendToMainProcess(response2.getFrameBytes());

            break;
        }
        case CalibrationMode::ELLIPSOID :
            break;
        case CalibrationMode::ELLIPSOID_DONE :
            emit signalBackPage();
            break;
        case CalibrationMode::MAGNETOMETER :
            emit signalBackPage();
            break;
        default:
            break;
    }
}

void CallibrationPage::fourthButton()
{
    switch (currentMode_)
    {
        case CalibrationMode::IDLE :
        {
            emit signalBackPage();
            break;
        }
        case CalibrationMode::ACCEL_ENABLE :
        {
            CalibrateAccelerometerCommand command(currentConfiguration_.accelerometer.axis, AccelAction::NEXT_AXIS);
            GUIWirelessComWrapperResponse response(command.getFrameBytes());
            controller_->sendToMainProcess(response.getFrameBytes());

            this_thread::sleep_for(std::chrono::milliseconds(200));

            CalibrateDataCommand calibrateDataCommand;
            GUIWirelessComWrapperResponse response2(calibrateDataCommand.getFrameBytes());
            controller_->sendToMainProcess(response2.getFrameBytes());

            break;
        }
        case CalibrationMode::ACCEL_DISABLE :
        {
            CalibrateAccelerometerCommand command(currentConfiguration_.accelerometer.axis, AccelAction::NEXT_AXIS);
            GUIWirelessComWrapperResponse response(command.getFrameBytes());
            controller_->sendToMainProcess(response.getFrameBytes());

            this_thread::sleep_for(std::chrono::milliseconds(200));

            CalibrateDataCommand calibrateDataCommand;
            GUIWirelessComWrapperResponse response2(calibrateDataCommand.getFrameBytes());
            controller_->sendToMainProcess(response2.getFrameBytes());

            break;
        }
        case CalibrationMode::ELLIPSOID :
        {
            emit signalBackPage();
            break;
        }
        case CalibrationMode::ELLIPSOID_DONE :
        {
            GUIWindowResponse bitsCommand(PagesType::BITS_PAGE);
            controller_->sendToMainProcess(bitsCommand.getFrameBytes());

            emit signalBITSPage();
            break;
        }
        case CalibrationMode::MAGNETOMETER :
        {
            CallibrateMagnetometerCommand command(Action::APPROVE);
            GUIWirelessComWrapperResponse response(command.getFrameBytes());
            controller_->sendToMainProcess(response.getFrameBytes());

            this_thread::sleep_for(std::chrono::milliseconds(200));

            CalibrateDataCommand calibrateDataCommand;
            GUIWirelessComWrapperResponse response2(calibrateDataCommand.getFrameBytes());
            controller_->sendToMainProcess(response2.getFrameBytes());

            break;
        }
        default:
            break;
    }
}

string CallibrationPage::getAxisName(uint8_t axis)
{
    string axisName;

    if(axis == 0)
        axisName = "x";
    else if (axis == 1)
        axisName = "y";
    else if (axis == 2)
        axisName = "z";
    else
        axisName = "?";

    return axisName;
}

string CallibrationPage::getCallibrationStatus(communication::CalibrationStatus status)
{
    switch (status)
    {
        case communication::CalibrationStatus::CALIB_PASSED :
            return string("PASSED");

        case communication::CalibrationStatus::CALIB_FAILED :
            return string("FAILED");

        case communication::CalibrationStatus::START_CALIBARTION :
            return string("START CALIBARTION");

        case communication::CalibrationStatus::IS_NOT_CALIBRATED :
            return string("IS NOT CALIBRATED");

        case communication::CalibrationStatus::CALIB_IN_THE_PROCESS :
            return string("IS CALIBRATING");

        case communication::CalibrationStatus::IS_CALIBRATED :
            return string("CALIBRATED");

        default:
            return string(" ");
    }
}
