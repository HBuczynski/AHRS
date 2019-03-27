#include "PlaneSettingsPage.h"
#include "ui_PlaneSettingsPage.h"

#include <iostream>

using namespace std;
using namespace peripherals;

PlaneSettingsPage::PlaneSettingsPage(gui::PageController *controller, QWidget *parent) :
    QWidget(parent),
    controller_(controller),
    ui_(new Ui::PlaneSettingsPage),
    currentOption_(0),
    MAX_OPTIONS_NUMBER(4)
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
    ui_->titleLabel->setStyleSheet("QLabel { color : white}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("CHOOSE A PLANE");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    // PLane Line
    QFont labelFont("Arial", 15, QFont::Bold);
    ui_->planeLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeLabel->setFont(labelFont);
    ui_->planeLabel->setText("CURRENT PLANE");

    ui_->planeDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeDotsLabel->setFont(labelFont);
    ui_->planeDotsLabel->setText("................................................................................................");

    QFont sqareFont("Arial", 22, QFont::Bold);
    ui_->planeValueLabel->setStyleSheet("QLabel { color : white}");
    ui_->planeValueLabel->setFont(sqareFont);
    ui_->planeValueLabel->setText("\u25FB\u25FB\u25FB\u25FB\u25FB\u25FB");

    // Plane from database line
    ui_->fromDatabaseLabel->setStyleSheet("QLabel { color : white}");
    ui_->fromDatabaseLabel->setFont(labelFont);
    ui_->fromDatabaseLabel->setText("FROM DATABASE");

    ui_->fromDatabaseDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->fromDatabaseDotsLabel->setFont(labelFont);
    ui_->fromDatabaseDotsLabel->setText("................................................................................................");

    ui_->fromDatabaseComboBox->setStyleSheet("background-color: rgb(255,255,255);border: none;");
    ui_->fromDatabaseComboBox->addItem("Test1");
    ui_->fromDatabaseComboBox->addItem("Test2");
    ui_->fromDatabaseComboBox->addItem("Test3");

    // New plane line
    ui_->newPlaneLabel->setStyleSheet("QLabel { color : white}");
    ui_->newPlaneLabel->setFont(labelFont);
    ui_->newPlaneLabel->setText("NEW PLANE");

    ui_->newPlaneDotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->newPlaneDotsLabel->setFont(labelFont);
    ui_->newPlaneDotsLabel->setText("................................................................................................");

    QFont newPlaneFont("Arial", 15, QFont::Bold);
    ui_->newPlaneLineEdit->setStyleSheet("background-color: rgb(255,255,255);border: none; ");
    ui_->newPlaneLineEdit->setFont(newPlaneFont);

    // Line Under buttons_
    ui_->dotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel->setFont(labelFont);
    ui_->dotsLabel->setText("................................................................................................"
                           "................................................................................................");

    keyboard_ = make_shared<Keyboard>();
    ui_->gridLayout->addWidget(keyboard_.get());

    QFont buttonFont("Arial", 15, QFont::Bold);
    ui_->nextLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");
    ui_->nextLabel->setFont(buttonFont);
    ui_->nextLabel->setAlignment(Qt::AlignCenter);
    ui_->nextLabel->setText("NEXT");

    ui_->menuLabel->setStyleSheet("QLabel { color: rgb(0,0,0); background: rgb(255,255,255);}");
    ui_->menuLabel->setFont(buttonFont);
    ui_->menuLabel->setAlignment(Qt::AlignCenter);
    ui_->menuLabel->setText("MENU");

    labels_[FieldType::COMBO_BOX] = ui_->fromDatabaseComboBox;
    labels_[FieldType::TEXT_FIELD] = ui_->newPlaneLineEdit;
    labels_[FieldType::MENU_LABEL] = ui_->menuLabel;
    labels_[FieldType::NEXT_LABEL] = ui_->nextLabel;
}

void PlaneSettingsPage::setupSlots()
{
    connect( ui_->newPlaneLineEdit, SIGNAL(textEdited()), this, SLOT(lineEditClicked()));
}

void PlaneSettingsPage::lineEditClicked()
{
    cout << "Lolo" << endl;
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
    labels_[static_cast<FieldType>(newOption)]->setStyleSheet("background-color: rgb(169,169,169);border: none;");
    currentOption_ = newOption;
}

void PlaneSettingsPage::cancelButton()
{

}

void PlaneSettingsPage::upButton()
{
    int8_t tempNumber = currentOption_ + 1;

    if(tempNumber >= MAX_OPTIONS_NUMBER)
    {
        tempNumber = tempNumber % MAX_OPTIONS_NUMBER;
    }

    highlightCurrentOption(tempNumber);
}

void PlaneSettingsPage::downButton()
{
    int8_t tempNumber = currentOption_ - 1;

    if(tempNumber<0)
    {
        tempNumber += MAX_OPTIONS_NUMBER;
    }

    highlightCurrentOption(tempNumber);
}

void PlaneSettingsPage::selectButton()
{
    const auto type = static_cast<FieldType>(currentOption_);

    switch (type)
    {
        case FieldType::COMBO_BOX :
        {
            break;
        }
        case FieldType::TEXT_FIELD :
        {
            break;
        }
        case FieldType::MENU_LABEL :
        {
            emit signalMENUPage();
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
