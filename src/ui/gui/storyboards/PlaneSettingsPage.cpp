#include "PlaneSettingsPage.h"
#include "ui_PlaneSettingsPage.h"

#include <interfaces/gui/GUIPlaneResponse.h>
#include <interfaces/gui/GUIWindowResponse.h>
#include <interfaces/gui/GUIWirelessComWrapperResponse.h>
#include <interfaces/wireless_commands/CalibrateDataCommand.h>

#include <functional>
#include <iostream>
#include <locale>

using namespace std;
using namespace peripherals;

std::string PlaneSettingsPage::planeNameTextField = "";
std::string PlaneSettingsPage::planeName = "";

PlaneSettingsPage::PlaneSettingsPage(gui::PageController *controller, const string& planes, QWidget *parent) :
    QWidget(parent),
    currentFieldType_(FieldType::GENERAL_SETTINGS),
    planes_(splitPlanes(planes)),
    controller_(controller),
    ui_(new Ui::PlaneSettingsPage),
    selectIsPresssed(false),
    currentOption_(0),
    currentItemInComboBox_(0),
    maxOptionsNumber_(4)
{
    ui_->setupUi(this);

    setupPage();
    highlightCurrentOption(currentOption_);
}

PlaneSettingsPage::~PlaneSettingsPage()
{
    delete ui_;
}

void PlaneSettingsPage::setupPage()
{
    this->setStyleSheet("background-color:black;");

    // Title label
    QFont font("Arial", 25, QFont::Bold);
    QFont labelFont("Arial", 15, QFont::Bold);
    QFont comboFont("Arial", 15, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color : white}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("CHOOSE A PLANE");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);


    planesFrame_ = make_shared<QFrame>(this);
    planesLayout_ = make_shared<QVBoxLayout>(planesFrame_.get());

    for(const auto& plane : planes_)
    {
        auto label = make_shared<QLabel>(this);

        label->setStyleSheet("QLabel { color : white}");
        label->setFont(comboFont);
        label->setStyleSheet("background-color: rgb(255,255,255);border: none; ");
        label->setText(plane.c_str());
        label->setAlignment(Qt::AlignCenter);
        label->setMinimumWidth(160);
        label->setMinimumHeight(35);

        planesLayout_->addWidget(label.get());
        planesLabels_.push_back(label);
    }

    planesFrame_->move(784, 125);
    planesFrame_->hide();

    ui_->planeLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeLabel->setFont(labelFont);
    ui_->planeLabel->setText("CURRENT PLANE");

    ui_->planeDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeDotsLabel->setFont(labelFont);
    ui_->planeDotsLabel->setText("................................................................................................");

    QFont sqareFont("Arial", 22, QFont::Bold);
    ui_->planeValueLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeValueLabel->setFont(sqareFont);

    // Plane from database line
    ui_->fromDatabaseLabel->setStyleSheet("QLabel { color : white}");
    ui_->fromDatabaseLabel->setFont(labelFont);
    ui_->fromDatabaseLabel->setText("FROM DATABASE");

    ui_->fromDatabaseDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->fromDatabaseDotsLabel->setFont(labelFont);
    ui_->fromDatabaseDotsLabel->setText("................................................................................................");

    ui_->fromDatabaseComboBox->setStyleSheet("QLabel { color : white}");
    ui_->fromDatabaseComboBox->setFont(comboFont);
    ui_->fromDatabaseComboBox->setStyleSheet("background-color: rgb(255,255,255);border: none; ");
    ui_->fromDatabaseComboBox->setText(planes_[0].c_str());
    ui_->fromDatabaseComboBox->setAlignment(Qt::AlignCenter);

    // New plane line
    ui_->newPlaneLabel->setStyleSheet("QLabel { color : white}");
    ui_->newPlaneLabel->setFont(labelFont);
    ui_->newPlaneLabel->setText("NEW PLANE");

    ui_->newPlaneDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->newPlaneDotsLabel->setFont(labelFont);
    ui_->newPlaneDotsLabel->setText("................................................................................................");

    QFont newPlaneFont("Arial", 19, QFont::Bold);
    ui_->newPlaneLineEdit->setStyleSheet("background-color: rgb(255,255,255);border: none; ");
    ui_->newPlaneLineEdit->setFont(newPlaneFont);
    ui_->newPlaneLineEdit->setText(planeNameTextField.c_str());

    // Line Under buttons_
    ui_->dotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel->setFont(labelFont);
    ui_->dotsLabel->setText("................................................................................................"
                           "................................................................................................");

    function< void(string) > callback = bind(&PlaneSettingsPage::setKeyClicked, this, placeholders::_1);
    keyboard_ = make_shared<Keyboard>(callback);
    ui_->gridLayout->addWidget(keyboard_.get());

    QFont buttonFont("Arial", 15, QFont::Bold);
    ui_->nextLabel->setFont(buttonFont);
    ui_->nextLabel->setAlignment(Qt::AlignCenter);
    ui_->nextLabel->setText("NEXT");

    ui_->confirmLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");
    ui_->confirmLabel->setFont(buttonFont);
    ui_->confirmLabel->setAlignment(Qt::AlignCenter);
    ui_->confirmLabel->setText("CONFIRM");

    ui_->menuLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");
    ui_->menuLabel->setFont(buttonFont);
    ui_->menuLabel->setAlignment(Qt::AlignCenter);
    ui_->menuLabel->setText("MENU");

    if(planeName.empty())
    {
        ui_->planeValueLabel->setText("\u25FB\u25FB\u25FB\u25FB\u25FB\u25FB");
        ui_->nextLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(128,128,128);}");
    }
    else
    {
        ui_->planeValueLabel->setText(planeName.c_str());
        ui_->fromDatabaseComboBox->setText(planeName.c_str());
        ui_->nextLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");
        maxOptionsNumber_ = 5;
    }

    labels_[FieldType::COMBO_BOX] = ui_->fromDatabaseComboBox;
    labels_[FieldType::TEXT_FIELD] = ui_->newPlaneLineEdit;
    labels_[FieldType::MENU_LABEL] = ui_->menuLabel;
    labels_[FieldType::CONFIRM_LABEL] = ui_->confirmLabel;
    labels_[FieldType::NEXT_LABEL] = ui_->nextLabel;
}

void PlaneSettingsPage::setupSlots()
{
    connect( ui_->newPlaneLineEdit, SIGNAL(textEdited()), this, SLOT(lineEditClicked()));
}

void PlaneSettingsPage::lineEditClicked()
{
}

void PlaneSettingsPage::initialize()
{
    map<SwitchCode, string> buttonNames;
    buttonNames[SwitchCode::FIRST_SWITCH] = "CANCEL";
    buttonNames[SwitchCode::SECOND_SWITCH] = "DOWN";
    buttonNames[SwitchCode::THIRD_SWITCH] = "UP";
    buttonNames[SwitchCode::FOURTH_SWITCH] = "SELECT";

    map<SwitchCode, function<void()> > callbackFunctions;
    callbackFunctions[SwitchCode::FIRST_SWITCH] = bind(&PlaneSettingsPage::cancelButton, this);
    callbackFunctions[SwitchCode::SECOND_SWITCH] = bind(&PlaneSettingsPage::upButton, this);
    callbackFunctions[SwitchCode::THIRD_SWITCH] = bind(&PlaneSettingsPage::downButton, this);
    callbackFunctions[SwitchCode::FOURTH_SWITCH] = bind(&PlaneSettingsPage::selectButton, this);

    QObject::connect(this, SIGNAL(signalMENUPage()), controller_, SLOT(setMenuPage()));
    QObject::connect(this, SIGNAL(signalCallibrationPage()), controller_, SLOT(setCallibrationPage()));

    initializeButtons(buttonNames, callbackFunctions);
}

void PlaneSettingsPage::initializeButtons(map<SwitchCode, string> name, map<SwitchCode, function<void()> > callbackFunctions)
{
    buttons_ = make_unique<Buttons>(this);
    buttons_->initialize(name, callbackFunctions);

    ui_->buttonLayout->addWidget(buttons_.get());
}

void PlaneSettingsPage::highlightCurrentOption(uint8_t newOption)
{
    labels_[static_cast<FieldType>(currentOption_)]->setStyleSheet("background-color: rgb(255,255,255);border: none;");
    labels_[static_cast<FieldType>(newOption)]->setStyleSheet("background-color: rgb(50,205,50);border: none;");
    currentOption_ = newOption;
}

void PlaneSettingsPage::highlightCurrentItem(uint8_t newOption)
{
    planesLabels_[currentItemInComboBox_]->setStyleSheet("background-color: rgb(255,255,255);border: none;");
    planesLabels_[newOption]->setStyleSheet("background-color: rgb(50,205,50);border: none;");
    currentItemInComboBox_ = newOption;
}

void PlaneSettingsPage::cancelButton()
{
    switch (currentFieldType_)
    {
        case FieldType::COMBO_BOX :
        {
            handleComboBoxCancel();
            break;
        }
        case FieldType::GENERAL_SETTINGS :
        {
            handleSettingsCancel();
            break;
        }
        default:
            break;
    }
}

void PlaneSettingsPage::handleSettingsCancel()
{
    const auto type = static_cast<FieldType>(currentOption_);
    switch (type)
    {
        case FieldType::COMBO_BOX :
        {
            selectIsPresssed = false;
            planesFrame_->hide();
            break;
        }
        case FieldType::TEXT_FIELD :
        {
            ui_->newPlaneLineEdit->setStyleSheet("background-color: rgb(50,205,50);border: none; ");
            selectIsPresssed = false;
            break;
        }
        case FieldType::MENU_LABEL :
        {
            break;
        }
        case FieldType::NEXT_LABEL :
        {
            break;
        }
        default:
            break;
    }
}

void PlaneSettingsPage::handleComboBoxCancel()
{
    planesFrame_->hide();
    currentFieldType_ = GENERAL_SETTINGS;
    selectIsPresssed = false;
}

void PlaneSettingsPage::upButton()
{
    switch (currentFieldType_)
    {
        case FieldType::COMBO_BOX :
        {
            handleComboBoxUP();
            break;
        }
        case FieldType::GENERAL_SETTINGS :
        {
            handleSettingsUP();
            break;
        }
        default:
            break;
    }
}

void PlaneSettingsPage::handleSettingsUP()
{
    if(selectIsPresssed)
        return;

    int8_t tempNumber = currentOption_ + 1;

    if(tempNumber >= maxOptionsNumber_)
    {
        tempNumber = tempNumber % maxOptionsNumber_;
    }

    highlightCurrentOption(tempNumber);
}

void PlaneSettingsPage::handleComboBoxUP()
{
    int8_t tempNumber = currentItemInComboBox_ + 1;

    if(tempNumber >= planesLabels_.size())
    {
        tempNumber = tempNumber % planesLabels_.size();
    }

    highlightCurrentItem(tempNumber);
}

void PlaneSettingsPage::downButton()
{
    switch (currentFieldType_)
    {
        case FieldType::COMBO_BOX :
        {
            handleComboBoxDown();
            break;
        }
        case FieldType::GENERAL_SETTINGS :
        {
            handleSettingsDown();
            break;
        }
        default:
            break;
    }
}

void PlaneSettingsPage::handleSettingsDown()
{
    if(selectIsPresssed)
        return;

    int8_t tempNumber = currentOption_ - 1;

    if(tempNumber<0)
    {
        tempNumber += maxOptionsNumber_;
    }

    highlightCurrentOption(tempNumber);
}

void PlaneSettingsPage::handleComboBoxDown()
{
    int8_t tempNumber = currentItemInComboBox_ - 1;

    if(tempNumber<0)
    {
        tempNumber += planesLabels_.size();
    }

    highlightCurrentItem(tempNumber);
}

void PlaneSettingsPage::selectButton()
{
    switch (currentFieldType_)
    {
        case FieldType::COMBO_BOX :
        {
            handleComboBoxSelect();
            break;
        }
        case FieldType::GENERAL_SETTINGS :
        {
            handleSettingsSelect();
            break;
        }
        default:
            break;
    }
}

void PlaneSettingsPage::handleSettingsSelect()
{
    const auto type = static_cast<FieldType>(currentOption_);

    switch (type)
    {
        case FieldType::COMBO_BOX :
        {
            selectIsPresssed = true;
            currentFieldType_ = COMBO_BOX;
            currentItemInComboBox_ = 0;
            planesLabels_[currentItemInComboBox_]->setStyleSheet("background-color: rgb(50,205,50);border: none;");

            planesFrame_->show();
            break;
        }
        case FieldType::TEXT_FIELD :
        {
            ui_->newPlaneLineEdit->setStyleSheet("background-color: rgb(144,238,144);border: none; ");
            selectIsPresssed = true;
            break;
        }
        case FieldType::MENU_LABEL :
        {
            emit signalMENUPage();
            break;
        }
        case FieldType::NEXT_LABEL :
        {
            communication::GUIPlaneResponse planeResponse(planeName);
            controller_->sendToMainProcess(planeResponse.getFrameBytes());

            this_thread::sleep_for(std::chrono::milliseconds(200));

            communication::GUIWindowResponse calibrationCommand(PagesType::CALLIBRATION_PAGE);
            controller_->sendToMainProcess(calibrationCommand.getFrameBytes());

            emit signalCallibrationPage();
            break;
        }
        case FieldType::CONFIRM_LABEL :
        {
            if(!planeNameTextField.empty())
            {
                planeName = planeNameTextField;
                planeNameTextField = "";
                ui_->newPlaneLineEdit->setText(planeNameTextField.c_str());
                ui_->planeValueLabel->setText(planeName.c_str());

                ui_->nextLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");
                maxOptionsNumber_ = 5;
            }
            break;
        }
        default:
            break;
    }
}

void PlaneSettingsPage::handleComboBoxSelect()
{
    selectIsPresssed = false;
    currentFieldType_ = GENERAL_SETTINGS;
    planeName = planes_[currentItemInComboBox_];

    ui_->fromDatabaseComboBox->setText(planeName.c_str());
    ui_->planeValueLabel->setText(planeName.c_str());
    planesFrame_->hide();

    ui_->nextLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");
    maxOptionsNumber_ = 5;
}

void PlaneSettingsPage::setKeyClicked(string name)
{
    const auto type = static_cast<FieldType>(currentOption_);

    if(selectIsPresssed && type == FieldType::TEXT_FIELD)
    {
        if(name == string("Backspace"))
            planeNameTextField = planeNameTextField.substr(0, planeNameTextField.size()-1);
        else
            planeNameTextField += name.c_str();

        ui_->newPlaneLineEdit->setText(planeNameTextField.c_str());
    }
}

vector<string> PlaneSettingsPage::splitPlanes(const string& name) const noexcept
{
    vector<string> planes;
    size_t begin, position = 0;

    const string MARKS{","};

    while( (begin = name.find_first_not_of(MARKS, position)) != string::npos)
    {
        position = name.find_first_of(MARKS, begin +1);
        planes.push_back(name.substr(begin, position - begin));
    }

    return planes;
}
