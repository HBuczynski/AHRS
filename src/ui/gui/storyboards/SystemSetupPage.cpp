#include "SystemSetupPage.h"

#include "ui_SystemSetupPage.h"
#include <QListWidgetItem>

SystemSetupPage::SystemSetupPage(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::SystemSetupPage)
{
    ui_->setupUi(this);
    setupPage();
}

SystemSetupPage::~SystemSetupPage()
{
    if(ui_)
    {
        delete ui_;
    }
}

void SystemSetupPage::setupPage()
{
    QFont font("Arial", 20, QFont::Bold);
    ui_->titleLabel_->setStyleSheet("QLabel { color : white}");
    ui_->titleLabel_->setFont(font);
    ui_->titleLabel_->setText("SYSTEM SETUP");

    QFont actionFont("Arial", 15, QFont::Bold);
    ui_->actionLabel_->setStyleSheet("QLabel { color : white}");
    ui_->actionLabel_->setFont(actionFont);
    ui_->actionLabel_->setText("ACTION");
    ui_->actionLabel_->setAlignment(Qt::AlignLeft);

    ui_->resultLabel_->setStyleSheet("QLabel { color : white}");
    ui_->resultLabel_->setFont(actionFont);
    ui_->resultLabel_->setText("RESULT");
    ui_->resultLabel_->setAlignment(Qt::AlignLeft);
}
