#include "RestartPage.h"
#include "ui_RestartPage.h"

RestartPage::RestartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RestartPage)
{
    ui->setupUi(this);

    setupPage();
}

RestartPage::~RestartPage()
{
    delete ui;
}

void RestartPage::setupPage()
{
    ui->verticalFrame->resize(QSize(1024, 600));

    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 40, QFont::Bold);
    ui->restartLabel->setStyleSheet("QLabel { color: rgb(255,0,0)}");
    ui->restartLabel->setFont(font);
    ui->restartLabel->setText("RESTART");
    ui->restartLabel->setAlignment(Qt::AlignCenter);

    QFont fontDescription("Arial", 20, QFont::Bold);
    ui->description->setStyleSheet("QLabel { color: rgb(255,0,0)}");
    ui->description->setFont(fontDescription);
    ui->description->setText("Sytem is going to restart and back to initial settings ...");
    ui->description->setAlignment(Qt::AlignCenter);
}
