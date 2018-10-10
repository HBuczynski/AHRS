/********************************************************************************
** Form generated from reading UI file 'MainPage.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

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

class Ui_MainPage
{
public:
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_2;
    QFrame *buttonFrame;
    QHBoxLayout *horizontalButtons;
    QGridLayout *buttonLayout;

    void setupUi(QWidget *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName(QStringLiteral("MainPage"));
        MainPage->resize(1024, 600);
        verticalFrame = new QFrame(MainPage);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setGeometry(QRect(0, 0, 1024, 600));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        titleLabel = new QLabel(verticalFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        buttonFrame = new QFrame(MainPage);
        buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
        buttonFrame->setGeometry(QRect(511, 560, 512, 40));
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


        retranslateUi(MainPage);

        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QWidget *MainPage)
    {
        MainPage->setWindowTitle(QApplication::translate("MainPage", "Form", Q_NULLPTR));
        titleLabel->setText(QApplication::translate("MainPage", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
