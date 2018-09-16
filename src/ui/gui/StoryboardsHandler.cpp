#include "StoryboardsHandler.h"

#include <iostream>

using namespace std;

StoryboardsHandler::StoryboardsHandler()
{}

void StoryboardsHandler::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
    {
        MainWindow->setObjectName(QStringLiteral("MainWindow"));
    }

    QPalette pal = MainWindow->palette();
    pal.setColor(QPalette::Window, Qt::black);

    MainWindow->resize(1024, 600);
    MainWindow->setMaximumSize(QSize(1024, 600));
    MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    MainWindow->setPalette(pal);

    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    centralWidget->setMaximumSize(QSize(1024, 600));

    gridLayout_5 = new QGridLayout(centralWidget);
    gridLayout_5->setSpacing(2);
    gridLayout_5->setContentsMargins(2, 2, 2, 2);
    gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));

    splitter = new QSplitter(centralWidget);
    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setEnabled(true);
    splitter->setMaximumSize(QSize(1024, 600));
    splitter->setOrientation(Qt::Horizontal);
    frame_2 = new QFrame(splitter);
    frame_2->setObjectName(QStringLiteral("frame_2"));
    frame_2->setMaximumSize(QSize(1024, 600));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);

    gridLayout_4 = new QGridLayout(frame_2);
    gridLayout_4->setSpacing(2);
    gridLayout_4->setContentsMargins(2, 2, 2, 2);
    gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
    gridLayout_4->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout_4->setContentsMargins(0, 3, 0, 3);
    gridLayout_2 = new QGridLayout();
    gridLayout_2->setSpacing(2);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayout_2->setSizeConstraint(QLayout::SetMaximumSize);

    widgetPFD = new WidgetPFD();
    widgetPFD->setObjectName(QStringLiteral("widgetPFD"));
    widgetPFD->setEnabled(true);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(2);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widgetPFD->sizePolicy().hasHeightForWidth());
    widgetPFD->setSizePolicy(sizePolicy);
    widgetPFD->setMaximumSize(QSize(1024, 600));

    welcomePage = new WelcomePage();
    welcomePage->resize(QSize(1024, 600));

    systemSetupPage_ = new SystemSetupPage();
    systemSetupPage_->resize(QSize(1024, 600));

    gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

    splitter->addWidget(frame_2);

    gridLayout_5->addWidget(splitter, 0, 0, 1, 1);

    MainWindow->setCentralWidget(centralWidget);

    QMetaObject::connectSlotsByName(MainWindow);
}

void StoryboardsHandler::setWelcomePage()
{
    gridLayout_2->addWidget(welcomePage, 0, 0, 2, 1);
}

void StoryboardsHandler::setWidgetPFDPage()
{
    gridLayout_2->addWidget(widgetPFD, 0, 0, 2, 1);
}

void StoryboardsHandler::setSystemSetupPage()
{
    gridLayout_2->addWidget(systemSetupPage_, 0, 0, 2, 1);
}
