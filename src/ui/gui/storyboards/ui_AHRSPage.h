/********************************************************************************
** Form generated from reading UI file 'AHRSPage.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AHRSPAGE_H
#define UI_AHRSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AHRSPage
{
public:
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout;
    QFrame *pdfFrame;
    QVBoxLayout *verticalLayout;
    QGridLayout *pfdLayout;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *devicesLayout;
    QFrame *buttonFrame;
    QHBoxLayout *horizontalButtons;
    QGridLayout *buttonLayout;
    QFrame *horizontalHeader_2;
    QHBoxLayout *horizontalHeader;
    QLabel *downFirst;
    QLabel *downGrdSpeed;
    QLabel *downAltGps;
    QLabel *downFltDuration;
    QLabel *downBoxPower;
    QLabel *downPowerSupply;
    QFrame *horizontalHeader_3;
    QHBoxLayout *horizontalHeader_4;
    QLabel *upFirst;
    QLabel *upGrdSpeed;
    QLabel *upAltGps;
    QLabel *upFltDuration;
    QLabel *upBoxPower;
    QLabel *upPowerSupply;

    void setupUi(QWidget *AHRSPage)
    {
        if (AHRSPage->objectName().isEmpty())
            AHRSPage->setObjectName(QStringLiteral("AHRSPage"));
        AHRSPage->resize(1024, 600);
        horizontalFrame = new QFrame(AHRSPage);
        horizontalFrame->setObjectName(QStringLiteral("horizontalFrame"));
        horizontalFrame->setGeometry(QRect(0, 0, 1024, 600));
        horizontalFrame->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        horizontalFrame->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(horizontalFrame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pdfFrame = new QFrame(horizontalFrame);
        pdfFrame->setObjectName(QStringLiteral("pdfFrame"));
        pdfFrame->setMinimumSize(QSize(600, 0));
        pdfFrame->setMaximumSize(QSize(600, 600));
        verticalLayout = new QVBoxLayout(pdfFrame);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pfdLayout = new QGridLayout();
        pfdLayout->setObjectName(QStringLiteral("pfdLayout"));

        verticalLayout->addLayout(pfdLayout);


        horizontalLayout->addWidget(pdfFrame);

        verticalFrame = new QFrame(horizontalFrame);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setMaximumSize(QSize(16777215, 530));
        verticalLayout_2 = new QVBoxLayout(verticalFrame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 8, 0, 0);
        devicesLayout = new QGridLayout();
        devicesLayout->setSpacing(0);
        devicesLayout->setObjectName(QStringLiteral("devicesLayout"));
        devicesLayout->setContentsMargins(-1, 10, -1, -1);

        verticalLayout_2->addLayout(devicesLayout);


        horizontalLayout->addWidget(verticalFrame);

        buttonFrame = new QFrame(AHRSPage);
        buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
        buttonFrame->setGeometry(QRect(512, 562, 512, 40));
        buttonFrame->setStyleSheet(QStringLiteral(""));
        buttonFrame->setLineWidth(0);
        horizontalButtons = new QHBoxLayout(buttonFrame);
        horizontalButtons->setSpacing(0);
        horizontalButtons->setObjectName(QStringLiteral("horizontalButtons"));
        horizontalButtons->setContentsMargins(0, 0, 0, 0);
        buttonLayout = new QGridLayout();
        buttonLayout->setSpacing(0);
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));

        horizontalButtons->addLayout(buttonLayout);

        horizontalHeader_2 = new QFrame(AHRSPage);
        horizontalHeader_2->setObjectName(QStringLiteral("horizontalHeader_2"));
        horizontalHeader_2->setGeometry(QRect(0, 20, 1024, 35));
        horizontalHeader_2->setStyleSheet(QStringLiteral(""));
        horizontalHeader_2->setLineWidth(0);
        horizontalHeader = new QHBoxLayout(horizontalHeader_2);
        horizontalHeader->setSpacing(3);
        horizontalHeader->setObjectName(QStringLiteral("horizontalHeader"));
        horizontalHeader->setContentsMargins(0, 0, 0, 0);
        downFirst = new QLabel(horizontalHeader_2);
        downFirst->setObjectName(QStringLiteral("downFirst"));
        downFirst->setStyleSheet(QStringLiteral("background-color: rgb(75,75, 75);"));
        downFirst->setAlignment(Qt::AlignCenter);

        horizontalHeader->addWidget(downFirst);

        downGrdSpeed = new QLabel(horizontalHeader_2);
        downGrdSpeed->setObjectName(QStringLiteral("downGrdSpeed"));
        downGrdSpeed->setStyleSheet(QStringLiteral("background-color: rgb(75,75, 75);"));
        downGrdSpeed->setAlignment(Qt::AlignCenter);

        horizontalHeader->addWidget(downGrdSpeed);

        downAltGps = new QLabel(horizontalHeader_2);
        downAltGps->setObjectName(QStringLiteral("downAltGps"));
        downAltGps->setStyleSheet(QStringLiteral("background-color: rgb(75,75, 75);"));
        downAltGps->setAlignment(Qt::AlignCenter);

        horizontalHeader->addWidget(downAltGps);

        downFltDuration = new QLabel(horizontalHeader_2);
        downFltDuration->setObjectName(QStringLiteral("downFltDuration"));
        downFltDuration->setStyleSheet(QStringLiteral("background-color: rgb(75,75, 75);"));
        downFltDuration->setAlignment(Qt::AlignCenter);

        horizontalHeader->addWidget(downFltDuration);

        downBoxPower = new QLabel(horizontalHeader_2);
        downBoxPower->setObjectName(QStringLiteral("downBoxPower"));
        downBoxPower->setStyleSheet(QStringLiteral("background-color: rgb(75,75, 75);"));
        downBoxPower->setAlignment(Qt::AlignCenter);

        horizontalHeader->addWidget(downBoxPower);

        downPowerSupply = new QLabel(horizontalHeader_2);
        downPowerSupply->setObjectName(QStringLiteral("downPowerSupply"));
        downPowerSupply->setStyleSheet(QStringLiteral("background-color: rgb(75,75, 75);"));
        downPowerSupply->setAlignment(Qt::AlignCenter);

        horizontalHeader->addWidget(downPowerSupply);

        horizontalHeader_3 = new QFrame(AHRSPage);
        horizontalHeader_3->setObjectName(QStringLiteral("horizontalHeader_3"));
        horizontalHeader_3->setGeometry(QRect(0, 0, 1024, 20));
        horizontalHeader_3->setStyleSheet(QStringLiteral(""));
        horizontalHeader_3->setLineWidth(0);
        horizontalHeader_4 = new QHBoxLayout(horizontalHeader_3);
        horizontalHeader_4->setSpacing(3);
        horizontalHeader_4->setObjectName(QStringLiteral("horizontalHeader_4"));
        horizontalHeader_4->setContentsMargins(0, 0, 0, 0);
        upFirst = new QLabel(horizontalHeader_3);
        upFirst->setObjectName(QStringLiteral("upFirst"));
        upFirst->setStyleSheet(QStringLiteral("background-color: rgb(45,45, 45);"));
        upFirst->setAlignment(Qt::AlignCenter);

        horizontalHeader_4->addWidget(upFirst);

        upGrdSpeed = new QLabel(horizontalHeader_3);
        upGrdSpeed->setObjectName(QStringLiteral("upGrdSpeed"));
        upGrdSpeed->setStyleSheet(QStringLiteral("background-color: rgb(45,45, 45);"));
        upGrdSpeed->setAlignment(Qt::AlignCenter);

        horizontalHeader_4->addWidget(upGrdSpeed);

        upAltGps = new QLabel(horizontalHeader_3);
        upAltGps->setObjectName(QStringLiteral("upAltGps"));
        upAltGps->setStyleSheet(QStringLiteral("background-color: rgb(45,45, 45);"));
        upAltGps->setAlignment(Qt::AlignCenter);

        horizontalHeader_4->addWidget(upAltGps);

        upFltDuration = new QLabel(horizontalHeader_3);
        upFltDuration->setObjectName(QStringLiteral("upFltDuration"));
        upFltDuration->setStyleSheet(QStringLiteral("background-color: rgb(45,45, 45);"));
        upFltDuration->setAlignment(Qt::AlignCenter);

        horizontalHeader_4->addWidget(upFltDuration);

        upBoxPower = new QLabel(horizontalHeader_3);
        upBoxPower->setObjectName(QStringLiteral("upBoxPower"));
        upBoxPower->setStyleSheet(QStringLiteral("background-color: rgb(45,45, 45);"));
        upBoxPower->setAlignment(Qt::AlignCenter);

        horizontalHeader_4->addWidget(upBoxPower);

        upPowerSupply = new QLabel(horizontalHeader_3);
        upPowerSupply->setObjectName(QStringLiteral("upPowerSupply"));
        upPowerSupply->setStyleSheet(QStringLiteral("background-color: rgb(45,45, 45);"));
        upPowerSupply->setAlignment(Qt::AlignCenter);

        horizontalHeader_4->addWidget(upPowerSupply);


        retranslateUi(AHRSPage);

        QMetaObject::connectSlotsByName(AHRSPage);
    } // setupUi

    void retranslateUi(QWidget *AHRSPage)
    {
        AHRSPage->setWindowTitle(QApplication::translate("AHRSPage", "Form", Q_NULLPTR));
        downFirst->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        downGrdSpeed->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        downAltGps->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        downFltDuration->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        downBoxPower->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        downPowerSupply->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        upFirst->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        upGrdSpeed->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        upAltGps->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        upFltDuration->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        upBoxPower->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
        upPowerSupply->setText(QApplication::translate("AHRSPage", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AHRSPage: public Ui_AHRSPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AHRSPAGE_H
