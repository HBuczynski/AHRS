#include "SystemSetupPage.h"

#include "ui_SystemSetupPage.h"
#include <QListWidgetItem>

SystemSetupPage::SystemSetupPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSetupPage)
{
    ui->setupUi(this);

    setupPage();
}

SystemSetupPage::~SystemSetupPage()
{
    delete ui;
}

void SystemSetupPage::setupPage()
{
   // ui->frame_->setStyleSheet("background-color:black;");

    QFont font("Arial", 20, QFont::Bold);
    ui->titleLabel_->setStyleSheet("QLabel { color : white}");
    ui->titleLabel_->setFont(font);
    ui->titleLabel_->setText("SYSTEM SETUP");

    QFont actionFont("Arial", 15, QFont::Bold);
    ui->actionLabel_->setStyleSheet("QLabel { color : white}");
    ui->actionLabel_->setFont(actionFont);
    ui->actionLabel_->setText("ACTION");
    ui->actionLabel_->setAlignment(Qt::AlignLeft);

    ui->resultLabel_->setStyleSheet("QLabel { color : white}");
    ui->resultLabel_->setFont(actionFont);
    ui->resultLabel_->setText("RESULT");
    ui->resultLabel_->setAlignment(Qt::AlignLeft);
}
