/********************************************************************************
** Form generated from reading UI file 'SystemSetupPage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SystemSetupPage_H
#define UI_SystemSetupPage_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemSetupPage
{
public:
    QFrame *frame_;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *titleLabel_;
    QListWidget *listWidget_;

    void setupUi(QWidget *SystemSetupPage)
    {
        if (SystemSetupPage->objectName().isEmpty())
            SystemSetupPage->setObjectName(QStringLiteral("SystemSetupPage"));
        SystemSetupPage->resize(1024, 600);
        frame_ = new QFrame(SystemSetupPage);
        frame_->setObjectName(QStringLiteral("frame_"));
        frame_->setGeometry(QRect(0, 0, 1024, 600));
        frame_->setFrameShape(QFrame::StyledPanel);
        frame_->setFrameShadow(QFrame::Raised);
        gridLayoutWidget = new QWidget(frame_);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 10, 1001, 581));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout->setContentsMargins(20, 20, 20, 20);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        titleLabel_ = new QLabel(gridLayoutWidget);
        titleLabel_->setObjectName(QStringLiteral("titleLabel_"));
        titleLabel_->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(titleLabel_, 0, 0, 1, 1);

        listWidget_ = new QListWidget(gridLayoutWidget);
        listWidget_->setObjectName(QStringLiteral("listWidget_"));

        gridLayout->addWidget(listWidget_, 2, 0, 1, 1);


        retranslateUi(SystemSetupPage);

        QMetaObject::connectSlotsByName(SystemSetupPage);
    } // setupUi

    void retranslateUi(QWidget *SystemSetupPage)
    {
        SystemSetupPage->setWindowTitle(QApplication::translate("SystemSetupPage", "Form", 0));
        titleLabel_->setText(QApplication::translate("SystemSetupPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class SystemSetupPage: public Ui_SystemSetupPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SystemSetupPage_H
