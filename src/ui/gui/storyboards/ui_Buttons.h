/********************************************************************************
** Form generated from reading UI file 'Buttons.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONS_H
#define UI_BUTTONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Buttons
{
public:
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *firstButton;
    QLabel *secondButton;
    QLabel *thirdButton;
    QLabel *fourthButton;

    void setupUi(QWidget *Buttons)
    {
        if (Buttons->objectName().isEmpty())
            Buttons->setObjectName(QStringLiteral("Buttons"));
        Buttons->resize(512, 40);
        horizontalFrame = new QFrame(Buttons);
        horizontalFrame->setObjectName(QStringLiteral("horizontalFrame"));
        horizontalFrame->setGeometry(QRect(0, 0, 512, 40));
        horizontalLayout = new QHBoxLayout(horizontalFrame);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        firstButton = new QLabel(horizontalFrame);
        firstButton->setObjectName(QStringLiteral("firstButton"));
        firstButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        firstButton->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(firstButton);

        secondButton = new QLabel(horizontalFrame);
        secondButton->setObjectName(QStringLiteral("secondButton"));
        secondButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        secondButton->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(secondButton);

        thirdButton = new QLabel(horizontalFrame);
        thirdButton->setObjectName(QStringLiteral("thirdButton"));
        thirdButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        thirdButton->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(thirdButton);

        fourthButton = new QLabel(horizontalFrame);
        fourthButton->setObjectName(QStringLiteral("fourthButton"));
        fourthButton->setMinimumSize(QSize(30, 0));
        fourthButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        fourthButton->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(fourthButton);


        retranslateUi(Buttons);

        QMetaObject::connectSlotsByName(Buttons);
    } // setupUi

    void retranslateUi(QWidget *Buttons)
    {
        Buttons->setWindowTitle(QApplication::translate("Buttons", "Form", 0));
        firstButton->setText(QApplication::translate("Buttons", "TextLabel", 0));
        secondButton->setText(QApplication::translate("Buttons", "TextLabel", 0));
        thirdButton->setText(QApplication::translate("Buttons", "TextLabel", 0));
        fourthButton->setText(QApplication::translate("Buttons", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Buttons: public Ui_Buttons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONS_H
