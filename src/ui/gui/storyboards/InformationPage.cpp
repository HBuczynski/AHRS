#include "InformationPage.h"
#include "ui_InformationPage.h"

InformationPage::InformationPage(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::InformationPage)
{
    ui_->setupUi(this);
    pageSetup();
}

InformationPage::~InformationPage()
{
    delete ui_;
}

void InformationPage::pageSetup()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("INFO");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    QFont labelFont("Arial", 15, QFont::Bold);
    ui_->lefLabel->setStyleSheet("QLabel { color : white}");
    ui_->lefLabel->setFont(labelFont);
    ui_->lefLabel->setText("CONNECTION MASTER");

    ui_->dotsLabel->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel->setFont(labelFont);
    ui_->dotsLabel->setText("................................................................................................");

    QFont sqareFont("Arial", 22, QFont::Bold);
    ui_->rightLabel->setStyleSheet("QLabel { color : white}");
    ui_->rightLabel->setFont(sqareFont);
    ui_->rightLabel->setText("\u25FB\u25FB\u25FB\u25FB\u25FB\u25FB");

    ui_->lefLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->lefLabel_2->setFont(labelFont);
    ui_->lefLabel_2->setText("CONNECTION SECONDARY");

    ui_->dotsLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_2->setFont(labelFont);
    ui_->dotsLabel_2->setText("................................................................................................");

    ui_->rightLabel_2->setStyleSheet("QLabel { color : white}");
    ui_->rightLabel_2->setFont(sqareFont);
    ui_->rightLabel_2->setText("\u25FB\u25FB\u25FB\u25FB\u25FB\u25FB");

    ui_->lefLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->lefLabel_3->setFont(labelFont);
    ui_->lefLabel_3->setText("BITS");

    ui_->dotsLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->dotsLabel_3->setFont(labelFont);
    ui_->dotsLabel_3->setText("................................................................................................");

    ui_->rightLabel_3->setStyleSheet("QLabel { color : white}");
    ui_->rightLabel_3->setFont(sqareFont);
    ui_->rightLabel_3->setText("\u25FB\u25FB\u25FB\u25FB\u25FB\u25FB");

    ui_->progressBar->setStyleSheet("QProgressBar {"
                                    "background-color: black;"
                                    "color: black;"
                                    "border-style: outset;"
                                    "border-width: 2px;"
                                    "border-color: black;"
                                    "border-radius: 7px;"
                                    "text-align: left; }"

                                    "QProgressBar::chunk {"
                                    "background-color: rgb(51,255,0); }");
}

void InformationPage::setMasterConnectionEstablished()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->rightLabel->setFont(sqareFont);
    ui_->rightLabel->setText("  TRUE");
    ui_->rightLabel->setAlignment(Qt::AlignLeft);
}

void InformationPage::setMasterConnectionFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel->setStyleSheet("QLabel { color: red}");
    ui_->rightLabel->setFont(sqareFont);
    ui_->rightLabel->setText("  FALSE");
    ui_->rightLabel->setAlignment(Qt::AlignLeft);
}

void InformationPage::setSecondaryConnectionEstablished()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_2->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->rightLabel_2->setFont(sqareFont);
    ui_->rightLabel_2->setText("  TRUE");
    ui_->rightLabel_2->setAlignment(Qt::AlignLeft);
}

void InformationPage::setSecondaryConnectionFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_2->setStyleSheet("QLabel { color: red}");
    ui_->rightLabel_2->setFont(sqareFont);
    ui_->rightLabel_2->setText("  FALSE");
    ui_->rightLabel_2->setAlignment(Qt::AlignLeft);
}

void InformationPage::setBITS()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_3->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->rightLabel_3->setFont(sqareFont);
    ui_->rightLabel_3->setText("  TRUE");
    ui_->rightLabel_3->setAlignment(Qt::AlignLeft);;
}

void InformationPage::setBITSFailed()
{
    QFont sqareFont("Arial", 18, QFont::Bold);
    ui_->rightLabel_3->setStyleSheet("QLabel { color: red}");
    ui_->rightLabel_3->setFont(sqareFont);
    ui_->rightLabel_3->setText("  FALSE");
    ui_->rightLabel_3->setAlignment(Qt::AlignLeft);;
}
