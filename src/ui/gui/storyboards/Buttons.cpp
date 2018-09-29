#include "Buttons.h"
#include "ui_Buttons.h"

Buttons::Buttons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Buttons)
{
    ui->setupUi(this);

    setup();
}

Buttons::~Buttons()
{
    delete ui;
}

void Buttons::setup()
{
    QFont font("Arial", 15, QFont::Bold);
    ui->firstButton->setStyleSheet("QLabel { color: cyan}");
    ui->firstButton->setFont(font);
    ui->firstButton->setText("RESTART");
    ui->firstButton->setAlignment(Qt::AlignCenter);

    ui->secondButton->setStyleSheet("QLabel { color: cyan }");
    ui->secondButton->setFont(font);
    ui->secondButton->setText("MENU");
    ui->secondButton->setAlignment(Qt::AlignCenter);

    ui->thirdButton->setStyleSheet("QLabel { color: cyan}");
    ui->thirdButton->setFont(font);
    ui->thirdButton->setText("LOGS");
    ui->thirdButton->setAlignment(Qt::AlignCenter);

    ui->fourthButton->setStyleSheet("QLabel { color: cyan}");
    ui->fourthButton->setFont(font);
    ui->fourthButton->setText("EXIT");
    ui->fourthButton->setAlignment(Qt::AlignCenter);
}
