/********************************************************************************
** Form generated from reading UI file 'GpsPage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPSPAGE_H
#define UI_GPSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GpsPage
{
public:
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_19;
    QLabel *latitudeLabel;
    QSpacerItem *horizontalSpacer_20;
    QLabel *dotsLabel_1;
    QSpacerItem *horizontalSpacer_21;
    QLabel *latitudeValue;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_6;
    QLabel *longitudeLabel;
    QSpacerItem *horizontalSpacer_16;
    QLabel *dotsLabel_2;
    QSpacerItem *horizontalSpacer_17;
    QLabel *longitudeValue;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_23;
    QLabel *headingLabel;
    QSpacerItem *horizontalSpacer_24;
    QLabel *dotsLabelHead;
    QSpacerItem *horizontalSpacer_25;
    QLabel *headingValue;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QLabel *satnumbLabel;
    QSpacerItem *horizontalSpacer_13;
    QLabel *dotsLabel_3;
    QSpacerItem *horizontalSpacer_14;
    QLabel *satnumValue;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QLabel *fixLabel;
    QSpacerItem *horizontalSpacer_11;
    QLabel *dotsLabel_4;
    QSpacerItem *horizontalSpacer_12;
    QLabel *fixValue;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QLabel *warningLabel;
    QSpacerItem *horizontalSpacer_9;
    QLabel *dotsLabel_5;
    QSpacerItem *horizontalSpacer_10;
    QLabel *warningValue;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;
    QFrame *buttonFrame;
    QHBoxLayout *horizontalButtons;
    QGridLayout *buttonLayout;

    void setupUi(QWidget *GpsPage)
    {
        if (GpsPage->objectName().isEmpty())
            GpsPage->setObjectName(QStringLiteral("GpsPage"));
        GpsPage->resize(1024, 600);
        verticalFrame = new QFrame(GpsPage);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setGeometry(QRect(0, 0, 1024, 600));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        titleLabel = new QLabel(verticalFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_19 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_19);

        latitudeLabel = new QLabel(verticalFrame);
        latitudeLabel->setObjectName(QStringLiteral("latitudeLabel"));
        latitudeLabel->setMinimumSize(QSize(160, 0));
        latitudeLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_9->addWidget(latitudeLabel);

        horizontalSpacer_20 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_20);

        dotsLabel_1 = new QLabel(verticalFrame);
        dotsLabel_1->setObjectName(QStringLiteral("dotsLabel_1"));
        dotsLabel_1->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(dotsLabel_1);

        horizontalSpacer_21 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_21);

        latitudeValue = new QLabel(verticalFrame);
        latitudeValue->setObjectName(QStringLiteral("latitudeValue"));
        latitudeValue->setMinimumSize(QSize(160, 0));
        latitudeValue->setMaximumSize(QSize(240, 16777215));
        latitudeValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(latitudeValue);

        horizontalSpacer_22 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_22);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalSpacer_6 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_6 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        longitudeLabel = new QLabel(verticalFrame);
        longitudeLabel->setObjectName(QStringLiteral("longitudeLabel"));
        longitudeLabel->setMinimumSize(QSize(160, 0));
        longitudeLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_8->addWidget(longitudeLabel);

        horizontalSpacer_16 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);

        dotsLabel_2 = new QLabel(verticalFrame);
        dotsLabel_2->setObjectName(QStringLiteral("dotsLabel_2"));
        dotsLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(dotsLabel_2);

        horizontalSpacer_17 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);

        longitudeValue = new QLabel(verticalFrame);
        longitudeValue->setObjectName(QStringLiteral("longitudeValue"));
        longitudeValue->setMinimumSize(QSize(160, 0));
        longitudeValue->setMaximumSize(QSize(240, 16777215));
        longitudeValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(longitudeValue);

        horizontalSpacer_18 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_18);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer_5 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_23 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_23);

        headingLabel = new QLabel(verticalFrame);
        headingLabel->setObjectName(QStringLiteral("headingLabel"));
        headingLabel->setMinimumSize(QSize(160, 0));
        headingLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_10->addWidget(headingLabel);

        horizontalSpacer_24 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_24);

        dotsLabelHead = new QLabel(verticalFrame);
        dotsLabelHead->setObjectName(QStringLiteral("dotsLabelHead"));
        dotsLabelHead->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(dotsLabelHead);

        horizontalSpacer_25 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_25);

        headingValue = new QLabel(verticalFrame);
        headingValue->setObjectName(QStringLiteral("headingValue"));
        headingValue->setMinimumSize(QSize(160, 0));
        headingValue->setMaximumSize(QSize(240, 16777215));
        headingValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(headingValue);

        horizontalSpacer_26 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_26);


        verticalLayout->addLayout(horizontalLayout_10);

        verticalSpacer_8 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_5 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        satnumbLabel = new QLabel(verticalFrame);
        satnumbLabel->setObjectName(QStringLiteral("satnumbLabel"));
        satnumbLabel->setMinimumSize(QSize(230, 0));
        satnumbLabel->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_7->addWidget(satnumbLabel);

        horizontalSpacer_13 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_13);

        dotsLabel_3 = new QLabel(verticalFrame);
        dotsLabel_3->setObjectName(QStringLiteral("dotsLabel_3"));
        dotsLabel_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(dotsLabel_3);

        horizontalSpacer_14 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_14);

        satnumValue = new QLabel(verticalFrame);
        satnumValue->setObjectName(QStringLiteral("satnumValue"));
        satnumValue->setMinimumSize(QSize(160, 0));
        satnumValue->setMaximumSize(QSize(240, 16777215));
        satnumValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(satnumValue);

        horizontalSpacer_15 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_15);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_4 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        fixLabel = new QLabel(verticalFrame);
        fixLabel->setObjectName(QStringLiteral("fixLabel"));
        fixLabel->setMinimumSize(QSize(140, 0));
        fixLabel->setMaximumSize(QSize(140, 16777215));

        horizontalLayout_6->addWidget(fixLabel);

        horizontalSpacer_11 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);

        dotsLabel_4 = new QLabel(verticalFrame);
        dotsLabel_4->setObjectName(QStringLiteral("dotsLabel_4"));
        dotsLabel_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(dotsLabel_4);

        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_12);

        fixValue = new QLabel(verticalFrame);
        fixValue->setObjectName(QStringLiteral("fixValue"));
        fixValue->setMinimumSize(QSize(160, 0));
        fixValue->setMaximumSize(QSize(240, 16777215));
        fixValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(fixValue);

        horizontalSpacer_8 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        warningLabel = new QLabel(verticalFrame);
        warningLabel->setObjectName(QStringLiteral("warningLabel"));
        warningLabel->setMinimumSize(QSize(160, 0));
        warningLabel->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_5->addWidget(warningLabel);

        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        dotsLabel_5 = new QLabel(verticalFrame);
        dotsLabel_5->setObjectName(QStringLiteral("dotsLabel_5"));
        dotsLabel_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(dotsLabel_5);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        warningValue = new QLabel(verticalFrame);
        warningValue->setObjectName(QStringLiteral("warningValue"));
        warningValue->setMinimumSize(QSize(160, 0));
        warningValue->setMaximumSize(QSize(240, 16777215));
        warningValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(warningValue);

        horizontalSpacer_7 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonFrame = new QFrame(GpsPage);
        buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
        buttonFrame->setGeometry(QRect(512, 560, 512, 40));
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


        retranslateUi(GpsPage);

        QMetaObject::connectSlotsByName(GpsPage);
    } // setupUi

    void retranslateUi(QWidget *GpsPage)
    {
        GpsPage->setWindowTitle(QApplication::translate("GpsPage", "Form", 0));
        titleLabel->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        latitudeLabel->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        dotsLabel_1->setText(QString());
        latitudeValue->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        longitudeLabel->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        dotsLabel_2->setText(QString());
        longitudeValue->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        headingLabel->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        dotsLabelHead->setText(QString());
        headingValue->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        satnumbLabel->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        dotsLabel_3->setText(QString());
        satnumValue->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        fixLabel->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        dotsLabel_4->setText(QString());
        fixValue->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        warningLabel->setText(QApplication::translate("GpsPage", "TextLabel", 0));
        dotsLabel_5->setText(QString());
        warningValue->setText(QApplication::translate("GpsPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class GpsPage: public Ui_GpsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPSPAGE_H
