/********************************************************************************
** Form generated from reading UI file 'InformationPage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONPAGE_H
#define UI_INFORMATIONPAGE_H

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

class Ui_InformationPage
{
public:
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_13;
    QLabel *masterLabel;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_comLabel;
    QSpacerItem *horizontalSpacer_6;
    QLabel *dotsLabel;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_comValue;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QLabel *m_imuLabel;
    QSpacerItem *horizontalSpacer_9;
    QLabel *dotsLabel_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *m_imuValue;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_gpsLabel;
    QSpacerItem *horizontalSpacer_11;
    QLabel *dotsLabel_3;
    QSpacerItem *horizontalSpacer_12;
    QLabel *m_gpsValue;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_14;
    QLabel *redundantLabel;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_17;
    QLabel *r_comLabel;
    QSpacerItem *horizontalSpacer_18;
    QLabel *dotsLabel_5;
    QSpacerItem *horizontalSpacer_19;
    QLabel *r_comValue;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_22;
    QLabel *r_imuLabel;
    QSpacerItem *horizontalSpacer_23;
    QLabel *dotsLabel_6;
    QSpacerItem *horizontalSpacer_24;
    QLabel *r_imuValue;
    QSpacerItem *horizontalSpacer_25;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_26;
    QLabel *r_gpsLabel;
    QSpacerItem *horizontalSpacer_27;
    QLabel *dotsLabel_7;
    QSpacerItem *horizontalSpacer_28;
    QLabel *r_gpsValue;
    QSpacerItem *horizontalSpacer_29;
    QSpacerItem *verticalSpacer_5;
    QFrame *buttonFrame;
    QHBoxLayout *horizontalButtons;
    QGridLayout *buttonLayout;

    void setupUi(QWidget *InformationPage)
    {
        if (InformationPage->objectName().isEmpty())
            InformationPage->setObjectName(QStringLiteral("InformationPage"));
        InformationPage->resize(1024, 600);
        verticalFrame = new QFrame(InformationPage);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setGeometry(QRect(0, 0, 1024, 600));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        titleLabel = new QLabel(verticalFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        verticalLayout->addWidget(titleLabel);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_13 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        masterLabel = new QLabel(verticalFrame);
        masterLabel->setObjectName(QStringLiteral("masterLabel"));
        masterLabel->setMinimumSize(QSize(230, 0));
        masterLabel->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_4->addWidget(masterLabel);

        horizontalSpacer_16 = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_16);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        m_comLabel = new QLabel(verticalFrame);
        m_comLabel->setObjectName(QStringLiteral("m_comLabel"));
        m_comLabel->setMinimumSize(QSize(230, 0));
        m_comLabel->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_3->addWidget(m_comLabel);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        dotsLabel = new QLabel(verticalFrame);
        dotsLabel->setObjectName(QStringLiteral("dotsLabel"));
        dotsLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(dotsLabel);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        m_comValue = new QLabel(verticalFrame);
        m_comValue->setObjectName(QStringLiteral("m_comValue"));
        m_comValue->setMinimumSize(QSize(90, 0));
        m_comValue->setMaximumSize(QSize(90, 16777215));
        m_comValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(m_comValue);

        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        m_imuLabel = new QLabel(verticalFrame);
        m_imuLabel->setObjectName(QStringLiteral("m_imuLabel"));
        m_imuLabel->setMinimumSize(QSize(80, 0));
        m_imuLabel->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(m_imuLabel);

        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        dotsLabel_2 = new QLabel(verticalFrame);
        dotsLabel_2->setObjectName(QStringLiteral("dotsLabel_2"));
        dotsLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(dotsLabel_2);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        m_imuValue = new QLabel(verticalFrame);
        m_imuValue->setObjectName(QStringLiteral("m_imuValue"));
        m_imuValue->setMinimumSize(QSize(90, 0));
        m_imuValue->setMaximumSize(QSize(90, 16777215));
        m_imuValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(m_imuValue);

        horizontalSpacer_7 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_4 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        m_gpsLabel = new QLabel(verticalFrame);
        m_gpsLabel->setObjectName(QStringLiteral("m_gpsLabel"));
        m_gpsLabel->setMinimumSize(QSize(80, 0));
        m_gpsLabel->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_6->addWidget(m_gpsLabel);

        horizontalSpacer_11 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);

        dotsLabel_3 = new QLabel(verticalFrame);
        dotsLabel_3->setObjectName(QStringLiteral("dotsLabel_3"));
        dotsLabel_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(dotsLabel_3);

        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_12);

        m_gpsValue = new QLabel(verticalFrame);
        m_gpsValue->setObjectName(QStringLiteral("m_gpsValue"));
        m_gpsValue->setMinimumSize(QSize(90, 0));
        m_gpsValue->setMaximumSize(QSize(90, 16777215));
        m_gpsValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_gpsValue);

        horizontalSpacer_8 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_6 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_14 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_14);

        redundantLabel = new QLabel(verticalFrame);
        redundantLabel->setObjectName(QStringLiteral("redundantLabel"));
        redundantLabel->setMinimumSize(QSize(230, 0));
        redundantLabel->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_7->addWidget(redundantLabel);

        horizontalSpacer_21 = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_21);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_17 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);

        r_comLabel = new QLabel(verticalFrame);
        r_comLabel->setObjectName(QStringLiteral("r_comLabel"));
        r_comLabel->setMinimumSize(QSize(230, 0));
        r_comLabel->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_8->addWidget(r_comLabel);

        horizontalSpacer_18 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_18);

        dotsLabel_5 = new QLabel(verticalFrame);
        dotsLabel_5->setObjectName(QStringLiteral("dotsLabel_5"));
        dotsLabel_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(dotsLabel_5);

        horizontalSpacer_19 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_19);

        r_comValue = new QLabel(verticalFrame);
        r_comValue->setObjectName(QStringLiteral("r_comValue"));
        r_comValue->setMinimumSize(QSize(90, 0));
        r_comValue->setMaximumSize(QSize(90, 16777215));
        r_comValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(r_comValue);

        horizontalSpacer_20 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_20);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer_10 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_22 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_22);

        r_imuLabel = new QLabel(verticalFrame);
        r_imuLabel->setObjectName(QStringLiteral("r_imuLabel"));
        r_imuLabel->setMinimumSize(QSize(80, 0));
        r_imuLabel->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_9->addWidget(r_imuLabel);

        horizontalSpacer_23 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_23);

        dotsLabel_6 = new QLabel(verticalFrame);
        dotsLabel_6->setObjectName(QStringLiteral("dotsLabel_6"));
        dotsLabel_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(dotsLabel_6);

        horizontalSpacer_24 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_24);

        r_imuValue = new QLabel(verticalFrame);
        r_imuValue->setObjectName(QStringLiteral("r_imuValue"));
        r_imuValue->setMinimumSize(QSize(90, 0));
        r_imuValue->setMaximumSize(QSize(90, 16777215));
        r_imuValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(r_imuValue);

        horizontalSpacer_25 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_25);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalSpacer_8 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_26 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_26);

        r_gpsLabel = new QLabel(verticalFrame);
        r_gpsLabel->setObjectName(QStringLiteral("r_gpsLabel"));
        r_gpsLabel->setMinimumSize(QSize(80, 0));
        r_gpsLabel->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_10->addWidget(r_gpsLabel);

        horizontalSpacer_27 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_27);

        dotsLabel_7 = new QLabel(verticalFrame);
        dotsLabel_7->setObjectName(QStringLiteral("dotsLabel_7"));
        dotsLabel_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(dotsLabel_7);

        horizontalSpacer_28 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_28);

        r_gpsValue = new QLabel(verticalFrame);
        r_gpsValue->setObjectName(QStringLiteral("r_gpsValue"));
        r_gpsValue->setMinimumSize(QSize(90, 0));
        r_gpsValue->setMaximumSize(QSize(90, 16777215));
        r_gpsValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(r_gpsValue);

        horizontalSpacer_29 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_29);


        verticalLayout->addLayout(horizontalLayout_10);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        buttonFrame = new QFrame(InformationPage);
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


        retranslateUi(InformationPage);

        QMetaObject::connectSlotsByName(InformationPage);
    } // setupUi

    void retranslateUi(QWidget *InformationPage)
    {
        InformationPage->setWindowTitle(QApplication::translate("InformationPage", "Form", 0));
        titleLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        masterLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        m_comLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        dotsLabel->setText(QString());
        m_comValue->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        m_imuLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        dotsLabel_2->setText(QString());
        m_imuValue->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        m_gpsLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        dotsLabel_3->setText(QString());
        m_gpsValue->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        redundantLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        r_comLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        dotsLabel_5->setText(QString());
        r_comValue->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        r_imuLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        dotsLabel_6->setText(QString());
        r_imuValue->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        r_gpsLabel->setText(QApplication::translate("InformationPage", "TextLabel", 0));
        dotsLabel_7->setText(QString());
        r_gpsValue->setText(QApplication::translate("InformationPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class InformationPage: public Ui_InformationPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONPAGE_H
