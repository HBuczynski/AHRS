#include "CallibrationPage.h"
#include "ui_CallibrationPage.h"

#include <interfaces/gui/GUICallibrationCommand.h>

using namespace std;
using namespace peripherals;

CallibrationPage::CallibrationPage(gui::PageController* controller, QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::CallibrationPage),
    controller_(controller)
{
    ui_->setupUi(this);
    setupPage();
}

CallibrationPage::~CallibrationPage()
{
    delete ui_;
}

void CallibrationPage::setupPage()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

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
    ui_->master_rightLabel->setText("OK");
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
    ui_->redundant_rightLabel->setText("OK");
    ui_->redundant_rightLabel->setAlignment(Qt::AlignRight);
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
    ui_->mXValueMin->setText("0");
    ui_->mXValueMin->setAlignment(Qt::AlignLeft);

    ui_->mYLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYLabelMin->setFont(fontTheSmallest);
    ui_->mYLabelMin->setText("Y:");
    ui_->mYLabelMin->setAlignment(Qt::AlignLeft);

    ui_->mYValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYValueMin->setFont(fontTheSmallest);
    ui_->mYValueMin->setText("0");
    ui_->mYValueMin->setAlignment(Qt::AlignLeft);

    ui_->mZLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZLabelMin->setFont(fontTheSmallest);
    ui_->mZLabelMin->setText("Z:");
    ui_->mZLabelMin->setAlignment(Qt::AlignLeft);

    ui_->mZValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZValueMin->setFont(fontTheSmallest);
    ui_->mZValueMin->setText("0");
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
    ui_->mXValueMax->setText("0");
    ui_->mXValueMax->setAlignment(Qt::AlignLeft);

    ui_->mYLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYLabelMax->setFont(fontTheSmallest);
    ui_->mYLabelMax->setText("Y:");
    ui_->mYLabelMax->setAlignment(Qt::AlignLeft);

    ui_->mYValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mYValueMax->setFont(fontTheSmallest);
    ui_->mYValueMax->setText("0");
    ui_->mYValueMax->setAlignment(Qt::AlignLeft);

    ui_->mZLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZLabelMax->setFont(fontTheSmallest);
    ui_->mZLabelMax->setText("Z:");
    ui_->mZLabelMax->setAlignment(Qt::AlignLeft);

    ui_->mZValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->mZValueMax->setFont(fontTheSmallest);
    ui_->mZValueMax->setText("0");
    ui_->mZValueMax->setAlignment(Qt::AlignLeft);
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
    ui_->magXValueMin->setText("0");
    ui_->magXValueMin->setAlignment(Qt::AlignLeft);

    ui_->magYLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYLabelMin->setFont(fontTheSmallest);
    ui_->magYLabelMin->setText("Y:");
    ui_->magYLabelMin->setAlignment(Qt::AlignLeft);

    ui_->magYValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYValueMin->setFont(fontTheSmallest);
    ui_->magYValueMin->setText("0");
    ui_->magYValueMin->setAlignment(Qt::AlignLeft);

    ui_->magZLabelMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZLabelMin->setFont(fontTheSmallest);
    ui_->magZLabelMin->setText("Z:");
    ui_->magZLabelMin->setAlignment(Qt::AlignLeft);

    ui_->magZValueMin->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZValueMin->setFont(fontTheSmallest);
    ui_->magZValueMin->setText("0");
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
    ui_->magXValueMax->setText("0");
    ui_->magXValueMax->setAlignment(Qt::AlignLeft);

    ui_->magYLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYLabelMax->setFont(fontTheSmallest);
    ui_->magYLabelMax->setText("Y:");
    ui_->magYLabelMax->setAlignment(Qt::AlignLeft);

    ui_->magYValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magYValueMax->setFont(fontTheSmallest);
    ui_->magYValueMax->setText("0");
    ui_->magYValueMax->setAlignment(Qt::AlignLeft);

    ui_->magZLabelMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZLabelMax->setFont(fontTheSmallest);
    ui_->magZLabelMax->setText("Z:");
    ui_->magZLabelMax->setAlignment(Qt::AlignLeft);

    ui_->magZValueMax->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->magZValueMax->setFont(fontTheSmallest);
    ui_->magZValueMax->setText("0");
    ui_->magZValueMax->setAlignment(Qt::AlignLeft);
}

void CallibrationPage::setEllipsoidParameters()
{
    QFont fontSmaller("Arial", 20, QFont::Bold);
    QFont fontTheSmallest("Arial", 15, QFont::Bold);

    ui_->ellipsoidLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->ellipsoidLabel->setFont(fontTheSmallest);
    ui_->ellipsoidLabel->setText("ELLIPSOID");
    ui_->ellipsoidLabel->setAlignment(Qt::AlignLeft);

    ui_->elLabel_1->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->elLabel_1->setFont(fontTheSmallest);
    ui_->elLabel_1->setText("---:");
    ui_->elLabel_1->setAlignment(Qt::AlignLeft);

    ui_->elValue_1->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_1->setFont(fontTheSmallest);
    ui_->elValue_1->setText("0 / 200");
    ui_->elValue_1->setAlignment(Qt::AlignLeft);

    ui_->elLabel_2->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_2->setFont(fontTheSmallest);
    ui_->elLabel_2->setText("+--:");
    ui_->elLabel_2->setAlignment(Qt::AlignLeft);

    ui_->elValue_2->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_2->setFont(fontTheSmallest);
    ui_->elValue_2->setText("0 / 200");
    ui_->elValue_2->setAlignment(Qt::AlignLeft);

    ui_->elLabel_3->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_3->setFont(fontTheSmallest);
    ui_->elLabel_3->setText("-+-:");
    ui_->elLabel_3->setAlignment(Qt::AlignLeft);

    ui_->elValue_3->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_3->setFont(fontTheSmallest);
    ui_->elValue_3->setText("0 / 200");
    ui_->elValue_3->setAlignment(Qt::AlignLeft);

    ui_->elLabel_4->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_4->setFont(fontTheSmallest);
    ui_->elLabel_4->setText("++-:");
    ui_->elLabel_4->setAlignment(Qt::AlignLeft);

    ui_->elValue_4->setStyleSheet("QLabel { color: rgb(255,255,255)}");
    ui_->elValue_4->setFont(fontTheSmallest);
    ui_->elValue_4->setText("0 / 200");
    ui_->elValue_4->setAlignment(Qt::AlignLeft);

    ui_->elLabel_5->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_5->setFont(fontTheSmallest);
    ui_->elLabel_5->setText("--+:");
    ui_->elLabel_5->setAlignment(Qt::AlignLeft);

    ui_->elValue_5->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_5->setFont(fontTheSmallest);
    ui_->elValue_5->setText("0 / 200");
    ui_->elValue_5->setAlignment(Qt::AlignLeft);

    ui_->elLabel_6->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_6->setFont(fontTheSmallest);
    ui_->elLabel_6->setText("+-+:");
    ui_->elLabel_6->setAlignment(Qt::AlignLeft);

    ui_->elValue_6->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_6->setFont(fontTheSmallest);
    ui_->elValue_6->setText("0 / 200");
    ui_->elValue_6->setAlignment(Qt::AlignLeft);

    ui_->elLabel_7->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_7->setFont(fontTheSmallest);
    ui_->elLabel_7->setText("-++:");
    ui_->elLabel_7->setAlignment(Qt::AlignLeft);

    ui_->elValue_7->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_7->setFont(fontTheSmallest);
    ui_->elValue_7->setText("0 / 200");
    ui_->elValue_7->setAlignment(Qt::AlignLeft);

    ui_->elLabel_8->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elLabel_8->setFont(fontTheSmallest);
    ui_->elLabel_8->setText("+++:");
    ui_->elLabel_8->setAlignment(Qt::AlignLeft);

    ui_->elValue_8->setStyleSheet("QLabel { color: rgb(250,250,250)}");
    ui_->elValue_8->setFont(fontTheSmallest);
    ui_->elValue_8->setText("0 / 200");
    ui_->elValue_8->setAlignment(Qt::AlignLeft);

    ui_->noteLabel->setStyleSheet("QLabel { color: rgb(250,0,0)}");
    ui_->noteLabel->setFont(fontSmaller);
    ui_->noteLabel->setText("Note:");
    ui_->noteLabel->setAlignment(Qt::AlignLeft);
}

void CallibrationPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "";
    buttonNames[SwitchCode::SECOND_SWITCH] = "";
    buttonNames[SwitchCode::THIRD_SWITCH] = "";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "< BACK";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&CallibrationPage::firstButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&CallibrationPage::secondButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&CallibrationPage::thirdButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&CallibrationPage::fourthButton, this);

    initializeButtons(buttonNames, callbackFunctions);

    QObject::connect(this, SIGNAL(signalBackPage()), controller_, SLOT(backToPreviousPage()));
}

void CallibrationPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void CallibrationPage::firstButton()
{

}

void CallibrationPage::secondButton()
{

}

void CallibrationPage::thirdButton()
{

}

void CallibrationPage::fourthButton()
{
    emit signalBackPage();
}

string CallibrationPage::getCallibrationStatus(int status)
{
    const auto type = static_cast<communication::CalibrationStatus>(status);

    switch (type)
    {
        case communication::CalibrationStatus::PASSED :
            return string("PASSED");

        case communication::CalibrationStatus::FAILED :
            return string("FAILED");

        case communication::CalibrationStatus::START_CALIBARTION :
            return string("START CALIBARTION");

        case communication::CalibrationStatus::IS_NOT_CALIBRATING :
            return string("IS NOT CALIBRATED");

        case communication::CalibrationStatus::IN_THE_PROCESS :
            return string("IS CALIBRATING");

        case communication::CalibrationStatus::IS_CALIBRATED :
            return string("CALIBRATED");

        default:
            return string(" ");
    }
}
