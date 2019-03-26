/********************************************************************************
** Form generated from reading UI file 'Keyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keyboard
{
public:
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *qButton;
    QPushButton *wButton;
    QPushButton *eButton;
    QPushButton *rButton;
    QPushButton *tButton;
    QPushButton *yButton;
    QPushButton *uButton;
    QPushButton *iButton;
    QPushButton *oButton;
    QPushButton *pButton;
    QPushButton *bpButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *aButton;
    QPushButton *sButton;
    QPushButton *dButton;
    QPushButton *fButton;
    QPushButton *gButton;
    QPushButton *hButton;
    QPushButton *jButton;
    QPushButton *kButton;
    QPushButton *lButton;
    QPushButton *apostropheButton;
    QPushButton *enterButton;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *numButton_1;
    QPushButton *zButton;
    QPushButton *xButton;
    QPushButton *cButton;
    QPushButton *vButton;
    QPushButton *bButton;
    QPushButton *nButton;
    QPushButton *mButton;
    QPushButton *commaButton;
    QPushButton *dotButton;
    QPushButton *questionButton;
    QPushButton *numButton_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *numButton_2;
    QPushButton *numButton_3;
    QPushButton *numButton_4;
    QPushButton *spaceButton;
    QPushButton *numButton_8;
    QPushButton *numButton_7;
    QPushButton *numButton_6;
    QSpacerItem *verticalSpacer_4;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *Keyboard)
    {
        if (Keyboard->objectName().isEmpty())
            Keyboard->setObjectName(QStringLiteral("Keyboard"));
        Keyboard->resize(761, 210);
        Keyboard->setMinimumSize(QSize(0, 210));
        Keyboard->setMaximumSize(QSize(16777215, 210));
        verticalFrame = new QFrame(Keyboard);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setGeometry(QRect(0, 0, 761, 220));
        verticalFrame->setMinimumSize(QSize(0, 220));
        verticalFrame->setMaximumSize(QSize(16777215, 220));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        qButton = new QPushButton(verticalFrame);
        qButton->setObjectName(QStringLiteral("qButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qButton->sizePolicy().hasHeightForWidth());
        qButton->setSizePolicy(sizePolicy);
        qButton->setMinimumSize(QSize(57, 43));
        qButton->setMaximumSize(QSize(58, 44));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(65, 65, 65, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        qButton->setPalette(palette);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        qButton->setFont(font);
        qButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout->addWidget(qButton);

        wButton = new QPushButton(verticalFrame);
        wButton->setObjectName(QStringLiteral("wButton"));
        sizePolicy.setHeightForWidth(wButton->sizePolicy().hasHeightForWidth());
        wButton->setSizePolicy(sizePolicy);
        wButton->setMinimumSize(QSize(57, 43));
        wButton->setMaximumSize(QSize(58, 44));
        wButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);\n"
"\n"
""));

        horizontalLayout->addWidget(wButton);

        eButton = new QPushButton(verticalFrame);
        eButton->setObjectName(QStringLiteral("eButton"));
        sizePolicy.setHeightForWidth(eButton->sizePolicy().hasHeightForWidth());
        eButton->setSizePolicy(sizePolicy);
        eButton->setMinimumSize(QSize(57, 43));
        eButton->setMaximumSize(QSize(58, 44));
        eButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);\n"
"\n"
""));

        horizontalLayout->addWidget(eButton);

        rButton = new QPushButton(verticalFrame);
        rButton->setObjectName(QStringLiteral("rButton"));
        sizePolicy.setHeightForWidth(rButton->sizePolicy().hasHeightForWidth());
        rButton->setSizePolicy(sizePolicy);
        rButton->setMinimumSize(QSize(57, 43));
        rButton->setMaximumSize(QSize(58, 44));
        rButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout->addWidget(rButton);

        tButton = new QPushButton(verticalFrame);
        tButton->setObjectName(QStringLiteral("tButton"));
        sizePolicy.setHeightForWidth(tButton->sizePolicy().hasHeightForWidth());
        tButton->setSizePolicy(sizePolicy);
        tButton->setMinimumSize(QSize(57, 43));
        tButton->setMaximumSize(QSize(58, 44));
        tButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(tButton);

        yButton = new QPushButton(verticalFrame);
        yButton->setObjectName(QStringLiteral("yButton"));
        sizePolicy.setHeightForWidth(yButton->sizePolicy().hasHeightForWidth());
        yButton->setSizePolicy(sizePolicy);
        yButton->setMinimumSize(QSize(57, 43));
        yButton->setMaximumSize(QSize(58, 44));
        yButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(yButton);

        uButton = new QPushButton(verticalFrame);
        uButton->setObjectName(QStringLiteral("uButton"));
        sizePolicy.setHeightForWidth(uButton->sizePolicy().hasHeightForWidth());
        uButton->setSizePolicy(sizePolicy);
        uButton->setMinimumSize(QSize(57, 43));
        uButton->setMaximumSize(QSize(58, 44));
        uButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(uButton);

        iButton = new QPushButton(verticalFrame);
        iButton->setObjectName(QStringLiteral("iButton"));
        sizePolicy.setHeightForWidth(iButton->sizePolicy().hasHeightForWidth());
        iButton->setSizePolicy(sizePolicy);
        iButton->setMinimumSize(QSize(57, 43));
        iButton->setMaximumSize(QSize(58, 44));
        iButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(iButton);

        oButton = new QPushButton(verticalFrame);
        oButton->setObjectName(QStringLiteral("oButton"));
        sizePolicy.setHeightForWidth(oButton->sizePolicy().hasHeightForWidth());
        oButton->setSizePolicy(sizePolicy);
        oButton->setMinimumSize(QSize(57, 43));
        oButton->setMaximumSize(QSize(58, 44));
        oButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(oButton);

        pButton = new QPushButton(verticalFrame);
        pButton->setObjectName(QStringLiteral("pButton"));
        sizePolicy.setHeightForWidth(pButton->sizePolicy().hasHeightForWidth());
        pButton->setSizePolicy(sizePolicy);
        pButton->setMinimumSize(QSize(57, 43));
        pButton->setMaximumSize(QSize(58, 44));
        pButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(pButton);

        bpButton = new QPushButton(verticalFrame);
        bpButton->setObjectName(QStringLiteral("bpButton"));
        sizePolicy.setHeightForWidth(bpButton->sizePolicy().hasHeightForWidth());
        bpButton->setSizePolicy(sizePolicy);
        bpButton->setMinimumSize(QSize(127, 44));
        bpButton->setMaximumSize(QSize(127, 44));
        bpButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(bpButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        aButton = new QPushButton(verticalFrame);
        buttonGroup = new QButtonGroup(Keyboard);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(aButton);
        aButton->setObjectName(QStringLiteral("aButton"));
        sizePolicy.setHeightForWidth(aButton->sizePolicy().hasHeightForWidth());
        aButton->setSizePolicy(sizePolicy);
        aButton->setMinimumSize(QSize(57, 43));
        aButton->setMaximumSize(QSize(58, 44));
        aButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(aButton);

        sButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(sButton);
        sButton->setObjectName(QStringLiteral("sButton"));
        sizePolicy.setHeightForWidth(sButton->sizePolicy().hasHeightForWidth());
        sButton->setSizePolicy(sizePolicy);
        sButton->setMinimumSize(QSize(57, 43));
        sButton->setMaximumSize(QSize(58, 44));
        sButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(sButton);

        dButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(dButton);
        dButton->setObjectName(QStringLiteral("dButton"));
        sizePolicy.setHeightForWidth(dButton->sizePolicy().hasHeightForWidth());
        dButton->setSizePolicy(sizePolicy);
        dButton->setMinimumSize(QSize(57, 43));
        dButton->setMaximumSize(QSize(58, 44));
        dButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(dButton);

        fButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(fButton);
        fButton->setObjectName(QStringLiteral("fButton"));
        sizePolicy.setHeightForWidth(fButton->sizePolicy().hasHeightForWidth());
        fButton->setSizePolicy(sizePolicy);
        fButton->setMinimumSize(QSize(57, 43));
        fButton->setMaximumSize(QSize(58, 44));
        fButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(fButton);

        gButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(gButton);
        gButton->setObjectName(QStringLiteral("gButton"));
        sizePolicy.setHeightForWidth(gButton->sizePolicy().hasHeightForWidth());
        gButton->setSizePolicy(sizePolicy);
        gButton->setMinimumSize(QSize(57, 43));
        gButton->setMaximumSize(QSize(58, 44));
        gButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(gButton);

        hButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(hButton);
        hButton->setObjectName(QStringLiteral("hButton"));
        sizePolicy.setHeightForWidth(hButton->sizePolicy().hasHeightForWidth());
        hButton->setSizePolicy(sizePolicy);
        hButton->setMinimumSize(QSize(57, 43));
        hButton->setMaximumSize(QSize(58, 44));
        hButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(hButton);

        jButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(jButton);
        jButton->setObjectName(QStringLiteral("jButton"));
        sizePolicy.setHeightForWidth(jButton->sizePolicy().hasHeightForWidth());
        jButton->setSizePolicy(sizePolicy);
        jButton->setMinimumSize(QSize(57, 43));
        jButton->setMaximumSize(QSize(58, 44));
        jButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(jButton);

        kButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(kButton);
        kButton->setObjectName(QStringLiteral("kButton"));
        sizePolicy.setHeightForWidth(kButton->sizePolicy().hasHeightForWidth());
        kButton->setSizePolicy(sizePolicy);
        kButton->setMinimumSize(QSize(57, 43));
        kButton->setMaximumSize(QSize(58, 44));
        kButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(kButton);

        lButton = new QPushButton(verticalFrame);
        lButton->setObjectName(QStringLiteral("lButton"));
        sizePolicy.setHeightForWidth(lButton->sizePolicy().hasHeightForWidth());
        lButton->setSizePolicy(sizePolicy);
        lButton->setMinimumSize(QSize(57, 43));
        lButton->setMaximumSize(QSize(58, 44));
        lButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(lButton);

        apostropheButton = new QPushButton(verticalFrame);
        buttonGroup->addButton(apostropheButton);
        apostropheButton->setObjectName(QStringLiteral("apostropheButton"));
        sizePolicy.setHeightForWidth(apostropheButton->sizePolicy().hasHeightForWidth());
        apostropheButton->setSizePolicy(sizePolicy);
        apostropheButton->setMinimumSize(QSize(57, 43));
        apostropheButton->setMaximumSize(QSize(58, 44));
        apostropheButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(apostropheButton);

        enterButton = new QPushButton(verticalFrame);
        enterButton->setObjectName(QStringLiteral("enterButton"));
        sizePolicy.setHeightForWidth(enterButton->sizePolicy().hasHeightForWidth());
        enterButton->setSizePolicy(sizePolicy);
        enterButton->setMinimumSize(QSize(110, 43));
        enterButton->setMaximumSize(QSize(110, 44));
        enterButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(enterButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        numButton_1 = new QPushButton(verticalFrame);
        numButton_1->setObjectName(QStringLiteral("numButton_1"));
        sizePolicy.setHeightForWidth(numButton_1->sizePolicy().hasHeightForWidth());
        numButton_1->setSizePolicy(sizePolicy);
        numButton_1->setMinimumSize(QSize(57, 43));
        numButton_1->setMaximumSize(QSize(58, 44));
        numButton_1->setStyleSheet(QLatin1String("background-color: rgb(40,40,40);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(numButton_1);

        zButton = new QPushButton(verticalFrame);
        zButton->setObjectName(QStringLiteral("zButton"));
        sizePolicy.setHeightForWidth(zButton->sizePolicy().hasHeightForWidth());
        zButton->setSizePolicy(sizePolicy);
        zButton->setMinimumSize(QSize(57, 43));
        zButton->setMaximumSize(QSize(58, 44));
        zButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(zButton);

        xButton = new QPushButton(verticalFrame);
        xButton->setObjectName(QStringLiteral("xButton"));
        sizePolicy.setHeightForWidth(xButton->sizePolicy().hasHeightForWidth());
        xButton->setSizePolicy(sizePolicy);
        xButton->setMinimumSize(QSize(57, 43));
        xButton->setMaximumSize(QSize(58, 44));
        xButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(xButton);

        cButton = new QPushButton(verticalFrame);
        cButton->setObjectName(QStringLiteral("cButton"));
        sizePolicy.setHeightForWidth(cButton->sizePolicy().hasHeightForWidth());
        cButton->setSizePolicy(sizePolicy);
        cButton->setMinimumSize(QSize(57, 43));
        cButton->setMaximumSize(QSize(58, 44));
        cButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(cButton);

        vButton = new QPushButton(verticalFrame);
        vButton->setObjectName(QStringLiteral("vButton"));
        sizePolicy.setHeightForWidth(vButton->sizePolicy().hasHeightForWidth());
        vButton->setSizePolicy(sizePolicy);
        vButton->setMinimumSize(QSize(57, 43));
        vButton->setMaximumSize(QSize(58, 44));
        vButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(vButton);

        bButton = new QPushButton(verticalFrame);
        bButton->setObjectName(QStringLiteral("bButton"));
        sizePolicy.setHeightForWidth(bButton->sizePolicy().hasHeightForWidth());
        bButton->setSizePolicy(sizePolicy);
        bButton->setMinimumSize(QSize(57, 43));
        bButton->setMaximumSize(QSize(58, 44));
        bButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(bButton);

        nButton = new QPushButton(verticalFrame);
        nButton->setObjectName(QStringLiteral("nButton"));
        sizePolicy.setHeightForWidth(nButton->sizePolicy().hasHeightForWidth());
        nButton->setSizePolicy(sizePolicy);
        nButton->setMinimumSize(QSize(57, 43));
        nButton->setMaximumSize(QSize(58, 44));
        nButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(nButton);

        mButton = new QPushButton(verticalFrame);
        mButton->setObjectName(QStringLiteral("mButton"));
        sizePolicy.setHeightForWidth(mButton->sizePolicy().hasHeightForWidth());
        mButton->setSizePolicy(sizePolicy);
        mButton->setMinimumSize(QSize(57, 43));
        mButton->setMaximumSize(QSize(58, 44));
        mButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(mButton);

        commaButton = new QPushButton(verticalFrame);
        commaButton->setObjectName(QStringLiteral("commaButton"));
        sizePolicy.setHeightForWidth(commaButton->sizePolicy().hasHeightForWidth());
        commaButton->setSizePolicy(sizePolicy);
        commaButton->setMinimumSize(QSize(57, 43));
        commaButton->setMaximumSize(QSize(58, 44));
        commaButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(commaButton);

        dotButton = new QPushButton(verticalFrame);
        dotButton->setObjectName(QStringLiteral("dotButton"));
        sizePolicy.setHeightForWidth(dotButton->sizePolicy().hasHeightForWidth());
        dotButton->setSizePolicy(sizePolicy);
        dotButton->setMinimumSize(QSize(57, 43));
        dotButton->setMaximumSize(QSize(58, 44));
        dotButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(dotButton);

        questionButton = new QPushButton(verticalFrame);
        questionButton->setObjectName(QStringLiteral("questionButton"));
        sizePolicy.setHeightForWidth(questionButton->sizePolicy().hasHeightForWidth());
        questionButton->setSizePolicy(sizePolicy);
        questionButton->setMinimumSize(QSize(57, 43));
        questionButton->setMaximumSize(QSize(58, 44));
        questionButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(questionButton);

        numButton_5 = new QPushButton(verticalFrame);
        numButton_5->setObjectName(QStringLiteral("numButton_5"));
        sizePolicy.setHeightForWidth(numButton_5->sizePolicy().hasHeightForWidth());
        numButton_5->setSizePolicy(sizePolicy);
        numButton_5->setMinimumSize(QSize(57, 43));
        numButton_5->setMaximumSize(QSize(58, 44));
        numButton_5->setStyleSheet(QLatin1String("background-color: rgb(40,40,40);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(numButton_5);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        numButton_2 = new QPushButton(verticalFrame);
        numButton_2->setObjectName(QStringLiteral("numButton_2"));
        sizePolicy.setHeightForWidth(numButton_2->sizePolicy().hasHeightForWidth());
        numButton_2->setSizePolicy(sizePolicy);
        numButton_2->setMinimumSize(QSize(57, 43));
        numButton_2->setMaximumSize(QSize(58, 44));
        numButton_2->setStyleSheet(QLatin1String("background-color: rgb(40,40,40);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(numButton_2);

        numButton_3 = new QPushButton(verticalFrame);
        numButton_3->setObjectName(QStringLiteral("numButton_3"));
        sizePolicy.setHeightForWidth(numButton_3->sizePolicy().hasHeightForWidth());
        numButton_3->setSizePolicy(sizePolicy);
        numButton_3->setMinimumSize(QSize(57, 43));
        numButton_3->setMaximumSize(QSize(58, 44));
        numButton_3->setStyleSheet(QLatin1String("background-color: rgb(40,40,40);\n"
""));

        horizontalLayout_4->addWidget(numButton_3);

        numButton_4 = new QPushButton(verticalFrame);
        numButton_4->setObjectName(QStringLiteral("numButton_4"));
        sizePolicy.setHeightForWidth(numButton_4->sizePolicy().hasHeightForWidth());
        numButton_4->setSizePolicy(sizePolicy);
        numButton_4->setMinimumSize(QSize(57, 43));
        numButton_4->setMaximumSize(QSize(58, 44));
        numButton_4->setStyleSheet(QLatin1String("background-color: rgb(40,40,40);\n"
""));

        horizontalLayout_4->addWidget(numButton_4);

        spaceButton = new QPushButton(verticalFrame);
        spaceButton->setObjectName(QStringLiteral("spaceButton"));
        sizePolicy.setHeightForWidth(spaceButton->sizePolicy().hasHeightForWidth());
        spaceButton->setSizePolicy(sizePolicy);
        spaceButton->setMinimumSize(QSize(375, 43));
        spaceButton->setMaximumSize(QSize(375, 44));
        spaceButton->setStyleSheet(QLatin1String("background-color: rgb(65,65,65);\n"
""));

        horizontalLayout_4->addWidget(spaceButton);

        numButton_8 = new QPushButton(verticalFrame);
        numButton_8->setObjectName(QStringLiteral("numButton_8"));
        sizePolicy.setHeightForWidth(numButton_8->sizePolicy().hasHeightForWidth());
        numButton_8->setSizePolicy(sizePolicy);
        numButton_8->setMinimumSize(QSize(57, 43));
        numButton_8->setMaximumSize(QSize(58, 44));
        numButton_8->setStyleSheet(QLatin1String("background-color: rgb(40,40,40);\n"
""));

        horizontalLayout_4->addWidget(numButton_8);

        numButton_7 = new QPushButton(verticalFrame);
        numButton_7->setObjectName(QStringLiteral("numButton_7"));
        sizePolicy.setHeightForWidth(numButton_7->sizePolicy().hasHeightForWidth());
        numButton_7->setSizePolicy(sizePolicy);
        numButton_7->setMinimumSize(QSize(57, 43));
        numButton_7->setMaximumSize(QSize(58, 44));
        numButton_7->setStyleSheet(QLatin1String("color: rgb(255, 255, 255); background-color: rgb(40,40,40);\n"
""));

        horizontalLayout_4->addWidget(numButton_7);

        numButton_6 = new QPushButton(verticalFrame);
        numButton_6->setObjectName(QStringLiteral("numButton_6"));
        sizePolicy.setHeightForWidth(numButton_6->sizePolicy().hasHeightForWidth());
        numButton_6->setSizePolicy(sizePolicy);
        numButton_6->setMinimumSize(QSize(57, 43));
        numButton_6->setMaximumSize(QSize(58, 44));
        numButton_6->setStyleSheet(QLatin1String("background-color: rgb(40,40,40);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(numButton_6);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        retranslateUi(Keyboard);

        QMetaObject::connectSlotsByName(Keyboard);
    } // setupUi

    void retranslateUi(QWidget *Keyboard)
    {
        Keyboard->setWindowTitle(QApplication::translate("Keyboard", "Form", 0));
        qButton->setText(QApplication::translate("Keyboard", "q", 0));
        wButton->setText(QApplication::translate("Keyboard", "w", 0));
        eButton->setText(QApplication::translate("Keyboard", "e", 0));
        rButton->setText(QApplication::translate("Keyboard", "r", 0));
        tButton->setText(QApplication::translate("Keyboard", "t", 0));
        yButton->setText(QApplication::translate("Keyboard", "y", 0));
        uButton->setText(QApplication::translate("Keyboard", "u", 0));
        iButton->setText(QApplication::translate("Keyboard", "i", 0));
        oButton->setText(QApplication::translate("Keyboard", "o", 0));
        pButton->setText(QApplication::translate("Keyboard", "p", 0));
        bpButton->setText(QString());
        aButton->setText(QApplication::translate("Keyboard", "a", 0));
        sButton->setText(QApplication::translate("Keyboard", "s", 0));
        dButton->setText(QApplication::translate("Keyboard", "d", 0));
        fButton->setText(QApplication::translate("Keyboard", "f", 0));
        gButton->setText(QApplication::translate("Keyboard", "g", 0));
        hButton->setText(QApplication::translate("Keyboard", "h", 0));
        jButton->setText(QApplication::translate("Keyboard", "j", 0));
        kButton->setText(QApplication::translate("Keyboard", "k", 0));
        lButton->setText(QApplication::translate("Keyboard", "l", 0));
        apostropheButton->setText(QApplication::translate("Keyboard", "'", 0));
        enterButton->setText(QApplication::translate("Keyboard", "Enter", 0));
        numButton_1->setText(QApplication::translate("Keyboard", "!", 0));
        zButton->setText(QApplication::translate("Keyboard", "z", 0));
        xButton->setText(QApplication::translate("Keyboard", "x", 0));
        cButton->setText(QApplication::translate("Keyboard", "c", 0));
        vButton->setText(QApplication::translate("Keyboard", "v", 0));
        bButton->setText(QApplication::translate("Keyboard", "b", 0));
        nButton->setText(QApplication::translate("Keyboard", "n", 0));
        mButton->setText(QApplication::translate("Keyboard", "m", 0));
        commaButton->setText(QApplication::translate("Keyboard", ",", 0));
        dotButton->setText(QApplication::translate("Keyboard", ".", 0));
        questionButton->setText(QApplication::translate("Keyboard", "?", 0));
        numButton_5->setText(QApplication::translate("Keyboard", "!", 0));
        numButton_2->setText(QApplication::translate("Keyboard", "?123", 0));
        numButton_3->setText(QString());
        numButton_4->setText(QString());
        spaceButton->setText(QString());
        numButton_8->setText(QString());
        numButton_7->setText(QApplication::translate("Keyboard", "?123", 0));
        numButton_6->setText(QApplication::translate("Keyboard", "kl", 0));
    } // retranslateUi

};

namespace Ui {
    class Keyboard: public Ui_Keyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
