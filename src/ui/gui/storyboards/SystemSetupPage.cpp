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
    ui->frame_->setStyleSheet("background-color:black;");

    ui->gridLayout->setSpacing(10);
    ui->gridLayout->setContentsMargins(20, 20, 20, 20);

    QFont font("Arial", 20, QFont::Bold);
    ui->titleLabel_->setStyleSheet("QLabel { color : white}");
    ui->titleLabel_->setFont(font);
    ui->titleLabel_->setText("SYSTEM SETUP");
    ui->titleLabel_->setAlignment(Qt::AlignCenter);

    QListWidgetItem *itm = new QListWidgetItem();
    itm->setText("My Item");

    itm->setFont(font);

    ui->listWidget_->insertItem(0, itm);
}
