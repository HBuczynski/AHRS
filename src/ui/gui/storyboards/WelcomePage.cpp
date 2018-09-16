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
    delete ui_;
}

void WelcomePage::setupPage()
{
    ui_->verticalFrame_->resize(QSize(1024, 600));

    QFont font("Arial", 60, QFont::Bold);
    ui_->ahrsLabel_->setStyleSheet("QLabel { color : white}");
    ui_->ahrsLabel_->setFont(font);
    ui_->ahrsLabel_->setText("AHRS SYSTEM");
    ui_->ahrsLabel_->setAlignment(Qt::AlignCenter);

    QFont fontDescription("Arial", 10, QFont::Bold);
    ui_->descriptionLabel_->setStyleSheet("QLabel { color : white}");
    ui_->descriptionLabel_->setFont(fontDescription);
    ui_->descriptionLabel_->setText("This system is not intended for professional use.");
    ui_->descriptionLabel_->setAlignment(Qt::AlignCenter);

    QFont fontAuthor("Arial", 10, QFont::Bold);
    ui_->authorLabel_->setStyleSheet("QLabel { color : white}");
    ui_->authorLabel_->setFont(fontAuthor);
    ui_->authorLabel_->setText("\u00A9 Copyright 2018 Hubert Buczyński");
    ui_->authorLabel_->setAlignment(Qt::AlignCenter);



}
