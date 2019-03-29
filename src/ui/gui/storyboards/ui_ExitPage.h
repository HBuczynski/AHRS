/********************************************************************************
** Form generated from reading UI file 'ExitPage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXITPAGE_H
#define UI_EXITPAGE_H

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

class Ui_ExitPage
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_2;
    QLabel *optionLabel;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *cancelLabel;
    QSpacerItem *horizontalSpacer_3;
    QLabel *restartLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *exitLabel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QFrame *buttonFrame;
    QHBoxLayout *horizontalButtons;
    QGridLayout *buttonLayout;

    void setupUi(QWidget *ExitPage)
    {
        if (ExitPage->objectName().isEmpty())
            ExitPage->setObjectName(QStringLiteral("ExitPage"));
        ExitPage->resize(1024, 600);
        verticalLayoutWidget = new QWidget(ExitPage);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, -1, 1021, 601));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(10, 170, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        titleLabel = new QLabel(verticalLayoutWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        optionLabel = new QLabel(verticalLayoutWidget);
        optionLabel->setObjectName(QStringLiteral("optionLabel"));

        verticalLayout->addWidget(optionLabel);

        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelLabel = new QLabel(verticalLayoutWidget);
        cancelLabel->setObjectName(QStringLiteral("cancelLabel"));
        cancelLabel->setMinimumSize(QSize(190, 0));
        cancelLabel->setMaximumSize(QSize(190, 16777215));

        horizontalLayout->addWidget(cancelLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        restartLabel = new QLabel(verticalLayoutWidget);
        restartLabel->setObjectName(QStringLiteral("restartLabel"));
        restartLabel->setMinimumSize(QSize(190, 0));
        restartLabel->setMaximumSize(QSize(190, 16777215));

        horizontalLayout->addWidget(restartLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        exitLabel = new QLabel(verticalLayoutWidget);
        exitLabel->setObjectName(QStringLiteral("exitLabel"));
        exitLabel->setMinimumSize(QSize(190, 0));
        exitLabel->setMaximumSize(QSize(190, 16777215));

        horizontalLayout->addWidget(exitLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        buttonFrame = new QFrame(ExitPage);
        buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
        buttonFrame->setGeometry(QRect(510, 560, 512, 40));
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


        retranslateUi(ExitPage);

        QMetaObject::connectSlotsByName(ExitPage);
    } // setupUi

    void retranslateUi(QWidget *ExitPage)
    {
        ExitPage->setWindowTitle(QApplication::translate("ExitPage", "Form", 0));
        titleLabel->setText(QApplication::translate("ExitPage", "TextLabel", 0));
        optionLabel->setText(QApplication::translate("ExitPage", "TextLabel", 0));
        cancelLabel->setText(QApplication::translate("ExitPage", "TextLabel", 0));
        restartLabel->setText(QApplication::translate("ExitPage", "TextLabel", 0));
        exitLabel->setText(QApplication::translate("ExitPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class ExitPage: public Ui_ExitPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXITPAGE_H
