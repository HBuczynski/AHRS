#include "CallibrationSettings.h"
#include "ui_CallibrationSettings.h"

#include <iostream>

using namespace std;

CallibrationSettings::CallibrationSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CallibrationSettings)
{
    ui->setupUi(this);

    setupPage();
}

CallibrationSettings::~CallibrationSettings()
{
    delete ui;
}

void CallibrationSettings::setupPage()
{
    this->setStyleSheet("background-color:black;");

    // Exit Button
    QFont exitFont("Arial", 13, QFont::Bold);
    ui->exitButton->setStyleSheet("QPushButton { background-color: white; }\n"
                                               "QPushButton:pressed { background-color: grey; }\n");
    ui->exitButton->setFont(exitFont);

    // Title label
    QFont font("Arial", 25, QFont::Bold);
    ui->titleLabel->setStyleSheet("QLabel { color : white}");
    ui->titleLabel->setFont(font);
    ui->titleLabel->setText("CHOOSE A PLANE");
    ui->titleLabel->setAlignment(Qt::AlignCenter);

    // PLane Line
    QFont labelFont("Arial", 15, QFont::Bold);
    ui->planeLabel->setStyleSheet("QLabel { color : white}");
    ui->planeLabel->setFont(labelFont);
    ui->planeLabel->setText("CURRENT PLANE");

    ui->planeDotsLabel->setStyleSheet("QLabel { color : white}");
    ui->planeDotsLabel->setFont(labelFont);
    ui->planeDotsLabel->setText("................................................................................................");

    QFont sqareFont("Arial", 22, QFont::Bold);
    ui->planeValueLabel->setStyleSheet("QLabel { color : white}");
    ui->planeValueLabel->setFont(sqareFont);
    ui->planeValueLabel->setText("\u25FB\u25FB\u25FB\u25FB\u25FB\u25FB");

    // Plane from database line
    ui->fromDatabaseLabel->setStyleSheet("QLabel { color : white}");
    ui->fromDatabaseLabel->setFont(labelFont);
    ui->fromDatabaseLabel->setText("FROM DATABASE");

    ui->fromDatabaseDotsLabel->setStyleSheet("QLabel { color : white}");
    ui->fromDatabaseDotsLabel->setFont(labelFont);
    ui->fromDatabaseDotsLabel->setText("................................................................................................");

    ui->fromDatabaseComboBox->setStyleSheet("background-color: rgb(255,255,255);border: none; ");

    // New plane line
    ui->newPlaneLabel->setStyleSheet("QLabel { color : white}");
    ui->newPlaneLabel->setFont(labelFont);
    ui->newPlaneLabel->setText("NEW PLANE");

    ui->newPlaneDotsLabel->setStyleSheet("QLabel { color : white}");
    ui->newPlaneDotsLabel->setFont(labelFont);
    ui->newPlaneDotsLabel->setText("................................................................................................");

    QFont newPlaneFont("Arial", 15, QFont::Bold);
    ui->newPlaneLineEdit->setStyleSheet("background-color: rgb(255,255,255);border: none; ");
    ui->newPlaneLineEdit->setFont(newPlaneFont);

    // Line Under buttons_
    ui->dotsLabel->setStyleSheet("QLabel { color : white}");
    ui->dotsLabel->setFont(labelFont);
    ui->dotsLabel->setText("................................................................................................"
                           "................................................................................................");

    keyboard_ = make_shared<Keyboard>();
    ui->gridLayout->addWidget(keyboard_.get());

    // Left button
    QFont buttonFont("Arial", 20, QFont::Bold);
    ui->leftButton->setStyleSheet("QPushButton { background-color: white; }\n"
                                  "QPushButton:pressed { background-color: grey; }\n");
    ui->leftButton->setFont(buttonFont);

    // Right button
    ui->rightButton->setStyleSheet("QPushButton { background-color: white; }\n"
                                   "QPushButton:pressed { background-color: grey; }\n");
    ui->rightButton->setFont(buttonFont);
}

void CallibrationSettings::setupSlots()
{
    connect( ui->newPlaneLineEdit, SIGNAL(textEdited()), this, SLOT(lineEditClicked()));
}

void CallibrationSettings::lineEditClicked()
{
    cout << "Lolo" << endl;
}