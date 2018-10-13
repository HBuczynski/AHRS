/********************************************************************************
** Form generated from reading UI file 'ConnectingPage.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTINGPAGE_H
#define UI_CONNECTINGPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectingPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *connectingLabel;
    QSpacerItem *verticalSpacer_2;
    QLabel *subTextLabel;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *ConnectingPage)
    {
        if (ConnectingPage->objectName().isEmpty())
            ConnectingPage->setObjectName(QStringLiteral("ConnectingPage"));
        ConnectingPage->resize(1024, 600);
        verticalLayout_2 = new QVBoxLayout(ConnectingPage);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalFrame = new QFrame(ConnectingPage);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        connectingLabel = new QLabel(verticalFrame);
        connectingLabel->setObjectName(QStringLiteral("connectingLabel"));

        verticalLayout->addWidget(connectingLabel);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        subTextLabel = new QLabel(verticalFrame);
        subTextLabel->setObjectName(QStringLiteral("subTextLabel"));

        verticalLayout->addWidget(subTextLabel);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        verticalLayout_2->addWidget(verticalFrame);


        retranslateUi(ConnectingPage);

        QMetaObject::connectSlotsByName(ConnectingPage);
    } // setupUi

    void retranslateUi(QWidget *ConnectingPage)
    {
        ConnectingPage->setWindowTitle(QApplication::translate("ConnectingPage", "Form", Q_NULLPTR));
        connectingLabel->setText(QApplication::translate("ConnectingPage", "TextLabel", Q_NULLPTR));
        subTextLabel->setText(QApplication::translate("ConnectingPage", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnectingPage: public Ui_ConnectingPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTINGPAGE_H
