/********************************************************************************
** Form generated from reading UI file 'WelcomePage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEPAGE_H
#define UI_WELCOMEPAGE_H

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

class Ui_WelcomePage
{
public:
    QFrame *verticalFrame_;
    QVBoxLayout *verticalLayout_;
    QSpacerItem *verticalSpacer_1;
    QLabel *ahrsLabel_;
    QSpacerItem *verticalSpacer;
    QLabel *acronymDescription;
    QSpacerItem *verticalSpacer_2;
    QLabel *descriptionLabel_;
    QSpacerItem *verticalSpacer_3;
    QLabel *authorLabel_;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *WelcomePage)
    {
        if (WelcomePage->objectName().isEmpty())
            WelcomePage->setObjectName(QStringLiteral("WelcomePage"));
        WelcomePage->resize(1024, 600);
        verticalFrame_ = new QFrame(WelcomePage);
        verticalFrame_->setObjectName(QStringLiteral("verticalFrame_"));
        verticalFrame_->setEnabled(true);
        verticalFrame_->setGeometry(QRect(0, 0, 1024, 600));
        verticalLayout_ = new QVBoxLayout(verticalFrame_);
        verticalLayout_->setObjectName(QStringLiteral("verticalLayout_"));
        verticalLayout_->setContentsMargins(0, -1, -1, -1);
        verticalSpacer_1 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_->addItem(verticalSpacer_1);

        ahrsLabel_ = new QLabel(verticalFrame_);
        ahrsLabel_->setObjectName(QStringLiteral("ahrsLabel_"));
        ahrsLabel_->setAlignment(Qt::AlignCenter);

        verticalLayout_->addWidget(ahrsLabel_);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_->addItem(verticalSpacer);

        acronymDescription = new QLabel(verticalFrame_);
        acronymDescription->setObjectName(QStringLiteral("acronymDescription"));
        acronymDescription->setAlignment(Qt::AlignCenter);

        verticalLayout_->addWidget(acronymDescription);

        verticalSpacer_2 = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_->addItem(verticalSpacer_2);

        descriptionLabel_ = new QLabel(verticalFrame_);
        descriptionLabel_->setObjectName(QStringLiteral("descriptionLabel_"));
        descriptionLabel_->setAlignment(Qt::AlignCenter);

        verticalLayout_->addWidget(descriptionLabel_);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_->addItem(verticalSpacer_3);

        authorLabel_ = new QLabel(verticalFrame_);
        authorLabel_->setObjectName(QStringLiteral("authorLabel_"));
        authorLabel_->setAlignment(Qt::AlignCenter);

        verticalLayout_->addWidget(authorLabel_);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_->addItem(verticalSpacer_4);


        retranslateUi(WelcomePage);

        QMetaObject::connectSlotsByName(WelcomePage);
    } // setupUi

    void retranslateUi(QWidget *WelcomePage)
    {
        WelcomePage->setWindowTitle(QApplication::translate("WelcomePage", "Form", 0));
        ahrsLabel_->setText(QApplication::translate("WelcomePage", "TextLabel", 0));
        acronymDescription->setText(QApplication::translate("WelcomePage", "TextLabel", 0));
        descriptionLabel_->setText(QApplication::translate("WelcomePage", "TextLabel", 0));
        authorLabel_->setText(QApplication::translate("WelcomePage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class WelcomePage: public Ui_WelcomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEPAGE_H
