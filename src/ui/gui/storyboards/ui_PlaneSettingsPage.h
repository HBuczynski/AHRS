/********************************************************************************
** Form generated from reading UI file 'PlaneSettingsPage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANESETTINGSPAGE_H
#define UI_PLANESETTINGSPAGE_H

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

class Ui_PlaneSettingsPage
{
public:
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *planeLabel;
    QSpacerItem *horizontalSpacer_6;
    QLabel *planeDotsLabel;
    QSpacerItem *horizontalSpacer_5;
    QLabel *planeValueLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *fromDatabaseLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *fromDatabaseDotsLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *fromDatabaseComboBox;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *newPlaneLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *newPlaneDotsLabel;
    QSpacerItem *horizontalSpacer_3;
    QLabel *newPlaneLineEdit;
    QSpacerItem *verticalSpacer_4;
    QFrame *keyboardFrame;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_6;
    QLabel *dotsLabel;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_9;
    QLabel *confirmLabel;
    QSpacerItem *horizontalSpacer_8;
    QLabel *menuLabel;
    QSpacerItem *horizontalSpacer_7;
    QLabel *nextLabel;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_8;
    QFrame *buttonFrame;
    QHBoxLayout *horizontalButtons;
    QGridLayout *buttonLayout;

    void setupUi(QWidget *PlaneSettingsPage)
    {
        if (PlaneSettingsPage->objectName().isEmpty())
            PlaneSettingsPage->setObjectName(QStringLiteral("PlaneSettingsPage"));
        PlaneSettingsPage->resize(1024, 600);
        verticalFrame = new QFrame(PlaneSettingsPage);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setGeometry(QRect(0, 0, 1024, 600));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(70, 10, 70, 30);
        verticalSpacer_2 = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        titleLabel = new QLabel(verticalFrame);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_5 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        planeLabel = new QLabel(verticalFrame);
        planeLabel->setObjectName(QStringLiteral("planeLabel"));
        planeLabel->setMinimumSize(QSize(200, 0));
        planeLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(planeLabel);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        planeDotsLabel = new QLabel(verticalFrame);
        planeDotsLabel->setObjectName(QStringLiteral("planeDotsLabel"));
        planeDotsLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(planeDotsLabel);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        planeValueLabel = new QLabel(verticalFrame);
        planeValueLabel->setObjectName(QStringLiteral("planeValueLabel"));
        planeValueLabel->setMinimumSize(QSize(160, 0));
        planeValueLabel->setMaximumSize(QSize(160, 16777215));
        planeValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(planeValueLabel);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fromDatabaseLabel = new QLabel(verticalFrame);
        fromDatabaseLabel->setObjectName(QStringLiteral("fromDatabaseLabel"));
        fromDatabaseLabel->setMinimumSize(QSize(200, 0));
        fromDatabaseLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(fromDatabaseLabel);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        fromDatabaseDotsLabel = new QLabel(verticalFrame);
        fromDatabaseDotsLabel->setObjectName(QStringLiteral("fromDatabaseDotsLabel"));

        horizontalLayout->addWidget(fromDatabaseDotsLabel);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        fromDatabaseComboBox = new QLabel(verticalFrame);
        fromDatabaseComboBox->setObjectName(QStringLiteral("fromDatabaseComboBox"));
        fromDatabaseComboBox->setMinimumSize(QSize(160, 35));
        fromDatabaseComboBox->setMaximumSize(QSize(160, 16777215));

        horizontalLayout->addWidget(fromDatabaseComboBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        newPlaneLabel = new QLabel(verticalFrame);
        newPlaneLabel->setObjectName(QStringLiteral("newPlaneLabel"));
        newPlaneLabel->setMinimumSize(QSize(200, 0));
        newPlaneLabel->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_4->addWidget(newPlaneLabel);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        newPlaneDotsLabel = new QLabel(verticalFrame);
        newPlaneDotsLabel->setObjectName(QStringLiteral("newPlaneDotsLabel"));

        horizontalLayout_4->addWidget(newPlaneDotsLabel);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        newPlaneLineEdit = new QLabel(verticalFrame);
        newPlaneLineEdit->setObjectName(QStringLiteral("newPlaneLineEdit"));
        newPlaneLineEdit->setMinimumSize(QSize(160, 30));
        newPlaneLineEdit->setMaximumSize(QSize(160, 16777215));
        newPlaneLineEdit->setAutoFillBackground(false);

        horizontalLayout_4->addWidget(newPlaneLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_4 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        keyboardFrame = new QFrame(verticalFrame);
        keyboardFrame->setObjectName(QStringLiteral("keyboardFrame"));
        keyboardFrame->setMinimumSize(QSize(800, 222));
        keyboardFrame->setMaximumSize(QSize(820, 16777215));
        gridLayoutWidget = new QWidget(keyboardFrame);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 801, 221));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout->addWidget(keyboardFrame, 0, Qt::AlignHCenter);

        verticalSpacer_6 = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        dotsLabel = new QLabel(verticalFrame);
        dotsLabel->setObjectName(QStringLiteral("dotsLabel"));
        dotsLabel->setMaximumSize(QSize(16777215, 10));

        verticalLayout->addWidget(dotsLabel);

        verticalSpacer_7 = new QSpacerItem(8, 3, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        confirmLabel = new QLabel(verticalFrame);
        confirmLabel->setObjectName(QStringLiteral("confirmLabel"));
        confirmLabel->setMinimumSize(QSize(120, 25));
        confirmLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(confirmLabel);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        menuLabel = new QLabel(verticalFrame);
        menuLabel->setObjectName(QStringLiteral("menuLabel"));
        menuLabel->setMinimumSize(QSize(120, 25));
        menuLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(menuLabel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        nextLabel = new QLabel(verticalFrame);
        nextLabel->setObjectName(QStringLiteral("nextLabel"));
        nextLabel->setMinimumSize(QSize(120, 25));
        nextLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(nextLabel);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);

        buttonFrame = new QFrame(PlaneSettingsPage);
        buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
        buttonFrame->setGeometry(QRect(512, 559, 512, 40));
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


        retranslateUi(PlaneSettingsPage);

        QMetaObject::connectSlotsByName(PlaneSettingsPage);
    } // setupUi

    void retranslateUi(QWidget *PlaneSettingsPage)
    {
        PlaneSettingsPage->setWindowTitle(QApplication::translate("PlaneSettingsPage", "Form", 0));
        titleLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        planeLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        planeDotsLabel->setText(QString());
        planeValueLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        fromDatabaseLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        fromDatabaseDotsLabel->setText(QString());
        fromDatabaseComboBox->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        newPlaneLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        newPlaneDotsLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        newPlaneLineEdit->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        dotsLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        confirmLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        menuLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
        nextLabel->setText(QApplication::translate("PlaneSettingsPage", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class PlaneSettingsPage: public Ui_PlaneSettingsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANESETTINGSPAGE_H
