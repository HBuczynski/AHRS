#include "MainPage.h"
#include "ui_MainPage.h"

using namespace std;

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::MainPage)
{
    ui_->setupUi(this);
    setupPage();
}

MainPage::~MainPage()
{
    delete ui_;
}

void MainPage::setupPage()
{
    ui_->verticalFrame->resize(QSize(1024, 600));
    this->setStyleSheet("background-color:black;");

    QFont font("Arial", 30, QFont::Bold);
    ui_->titleLabel->setStyleSheet("QLabel { color: rgb(51,255,0)}");
    ui_->titleLabel->setFont(font);
    ui_->titleLabel->setText("MAIN PAGE");
    ui_->titleLabel->setAlignment(Qt::AlignCenter);

    buttons_ = make_unique<Buttons>();
    ui_->buttonLayout->addWidget(buttons_.get());
}
