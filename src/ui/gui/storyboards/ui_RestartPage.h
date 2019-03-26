/********************************************************************************
** Form generated from reading UI file 'RestartPage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTARTPAGE_H
#define UI_RESTARTPAGE_H

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

class Ui_RestartPage
{
public:
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *restartLabel;
    QSpacerItem *verticalSpacer_2;
    QLabel *description;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *RestartPage)
    {
        if (RestartPage->objectName().isEmpty())
            RestartPage->setObjectName(QStringLiteral("RestartPage"));
        RestartPage->resize(1024, 600);
        verticalFrame = new QFrame(RestartPage);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setEnabled(true);
        verticalFrame->setGeometry(QRect(0, 0, 1024, 600));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 210, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        restartLabel = new QLabel(verticalFrame);
        restartLabel->setObjectName(QStringLiteral("restartLabel"));

        verticalLayout->addWidget(restartLabel);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        description = new QLabel(verticalFrame);
        description->setObjectName(QStringLiteral("description"));

        verticalLayout->addWidget(description);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(RestartPage);

        QMetaObject::connectSlotsByName(RestartPage);
    } // setupUi

    void retranslateUi(QWidget *RestartPage)
    {
        RestartPage->setWindowTitle(QApplication::translate("RestartPage", "Form", 0));
        restartLabel->setText(QApplication::translate("RestartPage", "TextLabel", 0));
        description->setText(QApplication::translate("RestartPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class RestartPage: public Ui_RestartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTARTPAGE_H
