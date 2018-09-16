/********************************************************************************
** Form generated from reading UI file 'SystemSetupPage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSETUPPAGE_H
#define UI_SYSTEMSETUPPAGE_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemSetupPage
{
public:
    QFrame *frame_;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *processLabel_;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *processResultLabel_;
    QHBoxLayout *horizontalLayout_2;
    QLabel *actionLabel_;
    QSpacerItem *horizontalSpacer;
    QLabel *resultLabel_;
    QSpacerItem *verticalSpacer_3;
    QLabel *titleLabel_;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SystemSetupPage)
    {
        if (SystemSetupPage->objectName().isEmpty())
            SystemSetupPage->setObjectName(QStringLiteral("SystemSetupPage"));
        SystemSetupPage->resize(1024, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SystemSetupPage->sizePolicy().hasHeightForWidth());
        SystemSetupPage->setSizePolicy(sizePolicy);
        frame_ = new QFrame(SystemSetupPage);
        frame_->setObjectName(QStringLiteral("frame_"));
        frame_->setGeometry(QRect(0, 0, 1024, 600));
        sizePolicy.setHeightForWidth(frame_->sizePolicy().hasHeightForWidth());
        frame_->setSizePolicy(sizePolicy);
        frame_->setFrameShape(QFrame::StyledPanel);
        frame_->setFrameShadow(QFrame::Raised);
        gridLayoutWidget = new QWidget(frame_);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 1001, 581));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout->setContentsMargins(20, 20, 20, 20);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        processLabel_ = new QLabel(gridLayoutWidget);
        processLabel_->setObjectName(QStringLiteral("processLabel_"));
        processLabel_->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(processLabel_);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        processResultLabel_ = new QLabel(gridLayoutWidget);
        processResultLabel_->setObjectName(QStringLiteral("processResultLabel_"));
        processResultLabel_->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(processResultLabel_);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        actionLabel_ = new QLabel(gridLayoutWidget);
        actionLabel_->setObjectName(QStringLiteral("actionLabel_"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(actionLabel_->sizePolicy().hasHeightForWidth());
        actionLabel_->setSizePolicy(sizePolicy1);
        actionLabel_->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(actionLabel_);

        horizontalSpacer = new QSpacerItem(550, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        resultLabel_ = new QLabel(gridLayoutWidget);
        resultLabel_->setObjectName(QStringLiteral("resultLabel_"));
        sizePolicy1.setHeightForWidth(resultLabel_->sizePolicy().hasHeightForWidth());
        resultLabel_->setSizePolicy(sizePolicy1);
        resultLabel_->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(resultLabel_);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 3, 0, 1, 1);

        titleLabel_ = new QLabel(gridLayoutWidget);
        titleLabel_->setObjectName(QStringLiteral("titleLabel_"));
        sizePolicy1.setHeightForWidth(titleLabel_->sizePolicy().hasHeightForWidth());
        titleLabel_->setSizePolicy(sizePolicy1);
        titleLabel_->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(titleLabel_, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 5, 0, 1, 1);


        retranslateUi(SystemSetupPage);

        QMetaObject::connectSlotsByName(SystemSetupPage);
    } // setupUi

    void retranslateUi(QWidget *SystemSetupPage)
    {
        SystemSetupPage->setWindowTitle(QApplication::translate("SystemSetupPage", "Form", 0));
        processLabel_->setText(QString());
        label_2->setText(QApplication::translate("SystemSetupPage", "TextLabel", 0));
        processResultLabel_->setText(QApplication::translate("SystemSetupPage", "TextLabel", 0));
        actionLabel_->setText(QApplication::translate("SystemSetupPage", "TextLabel", 0));
        resultLabel_->setText(QApplication::translate("SystemSetupPage", "TextLabel", 0));
        titleLabel_->setText(QApplication::translate("SystemSetupPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class SystemSetupPage: public Ui_SystemSetupPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSETUPPAGE_H
