/********************************************************************************
** Form generated from reading UI file 'InformationPage.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
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
    QHBoxLayout *horizontalLayout_3;
    QLabel *lefLabel;
    QSpacerItem *horizontalSpacer_6;
    QLabel *dotsLabel;
    QSpacerItem *horizontalSpacer_5;
    QLabel *rightLabel;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lefLabel_2;
    QSpacerItem *horizontalSpacer_9;
    QLabel *dotsLabel_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *rightLabel_2;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lefLabel_3;
    QSpacerItem *horizontalSpacer_11;
    QLabel *dotsLabel_3;
    QSpacerItem *horizontalSpacer_12;
    QLabel *rightLabel_3;
    QSpacerItem *verticalSpacer_5;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_6;

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

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lefLabel = new QLabel(verticalFrame);
        lefLabel->setObjectName(QStringLiteral("lefLabel"));
        lefLabel->setMinimumSize(QSize(280, 0));
        lefLabel->setMaximumSize(QSize(280, 16777215));

        horizontalLayout_3->addWidget(lefLabel);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        dotsLabel = new QLabel(verticalFrame);
        dotsLabel->setObjectName(QStringLiteral("dotsLabel"));
        dotsLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(dotsLabel);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        rightLabel = new QLabel(verticalFrame);
        rightLabel->setObjectName(QStringLiteral("rightLabel"));
        rightLabel->setMinimumSize(QSize(160, 0));
        rightLabel->setMaximumSize(QSize(160, 16777215));
        rightLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(rightLabel);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lefLabel_2 = new QLabel(verticalFrame);
        lefLabel_2->setObjectName(QStringLiteral("lefLabel_2"));
        lefLabel_2->setMinimumSize(QSize(280, 0));
        lefLabel_2->setMaximumSize(QSize(280, 16777215));

        horizontalLayout_5->addWidget(lefLabel_2);

        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        dotsLabel_2 = new QLabel(verticalFrame);
        dotsLabel_2->setObjectName(QStringLiteral("dotsLabel_2"));
        dotsLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(dotsLabel_2);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        rightLabel_2 = new QLabel(verticalFrame);
        rightLabel_2->setObjectName(QStringLiteral("rightLabel_2"));
        rightLabel_2->setMinimumSize(QSize(160, 0));
        rightLabel_2->setMaximumSize(QSize(160, 16777215));
        rightLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(rightLabel_2);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lefLabel_3 = new QLabel(verticalFrame);
        lefLabel_3->setObjectName(QStringLiteral("lefLabel_3"));
        lefLabel_3->setMinimumSize(QSize(280, 0));
        lefLabel_3->setMaximumSize(QSize(280, 16777215));

        horizontalLayout_6->addWidget(lefLabel_3);

        horizontalSpacer_11 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);

        dotsLabel_3 = new QLabel(verticalFrame);
        dotsLabel_3->setObjectName(QStringLiteral("dotsLabel_3"));
        dotsLabel_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(dotsLabel_3);

        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_12);

        rightLabel_3 = new QLabel(verticalFrame);
        rightLabel_3->setObjectName(QStringLiteral("rightLabel_3"));
        rightLabel_3->setMinimumSize(QSize(160, 0));
        rightLabel_3->setMaximumSize(QSize(160, 16777215));
        rightLabel_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(rightLabel_3);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        progressBar = new QProgressBar(verticalFrame);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);

        verticalLayout->addWidget(progressBar);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_6);


        retranslateUi(InformationPage);

        QMetaObject::connectSlotsByName(InformationPage);
    } // setupUi

    void retranslateUi(QWidget *InformationPage)
    {
        InformationPage->setWindowTitle(QApplication::translate("InformationPage", "Form", Q_NULLPTR));
        titleLabel->setText(QApplication::translate("InformationPage", "TextLabel", Q_NULLPTR));
        lefLabel->setText(QApplication::translate("InformationPage", "TextLabel", Q_NULLPTR));
        dotsLabel->setText(QString());
        rightLabel->setText(QApplication::translate("InformationPage", "TextLabel", Q_NULLPTR));
        lefLabel_2->setText(QApplication::translate("InformationPage", "TextLabel", Q_NULLPTR));
        dotsLabel_2->setText(QString());
        rightLabel_2->setText(QApplication::translate("InformationPage", "TextLabel", Q_NULLPTR));
        lefLabel_3->setText(QApplication::translate("InformationPage", "TextLabel", Q_NULLPTR));
        dotsLabel_3->setText(QString());
        rightLabel_3->setText(QApplication::translate("InformationPage", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InformationPage: public Ui_InformationPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONPAGE_H
