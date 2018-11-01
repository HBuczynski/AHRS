#include "WelcomePage.h"

#include "ui_WelcomePage.h"

#include <QFont>

WelcomePage::WelcomePage(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::WelcomePage)
{
    ui_->setupUi(this);

    setupPage();
}

WelcomePage::~WelcomePage()
{
    if(ui_)
    {
        delete ui_;
    }
}

void WelcomePage::setupPage()
{
    ui_->verticalFrame_->resize(QSize(1024, 600));

    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 70, QFont::Bold);
    ui_->ahrsLabel_->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->ahrsLabel_->setFont(font);
    ui_->ahrsLabel_->setText("A  H  R  S");
    ui_->ahrsLabel_->setAlignment(Qt::AlignCenter);

    QFont fontDec("Arial", 20, QFont::Bold);
    ui_->acronymDescription->setStyleSheet("QLabel { color : rgb(51,255,0)}");
    ui_->acronymDescription->setFont(fontDec);
    ui_->acronymDescription->setText("Attitude Heading Reference System");
    ui_->acronymDescription->setAlignment(Qt::AlignCenter);

    QFont fontDescription("Arial", 15, QFont::Bold);
    ui_->descriptionLabel_->setStyleSheet("QLabel { color : rgb(51,255,0)}");
    ui_->descriptionLabel_->setFont(fontDescription);
    ui_->descriptionLabel_->setText("This system is not intended for professional use.");
    ui_->descriptionLabel_->setAlignment(Qt::AlignCenter);

    QFont fontAuthor("Arial", 15, QFont::Bold);
    ui_->authorLabel_->setStyleSheet("QLabel { color : rgb(51,255,0)}");
    ui_->authorLabel_->setFont(fontAuthor);
    ui_->authorLabel_->setText("\u00A9 Copyright by Hubert Buczyński");
    ui_->authorLabel_->setAlignment(Qt::AlignCenter);

}
