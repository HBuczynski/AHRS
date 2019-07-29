#include "Keyboard.h"
#include "ui_Keyboard.h"

#include <iostream>

using namespace std;

Keyboard::Keyboard(std::function<void(std::string)> callback, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard),
    keyboardCounter_(0),
    previousTime_(std::chrono::system_clock::now()),
    charCallback_(callback)
{
    ui->setupUi(this);

    initialize();
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::initialize()
{
    initializeFont();
    initializeSlots();
}

void Keyboard::setInitButton()
{
    buttons[keyboardCounter_]->setStyleSheet("background-color: rgb(144,238,144); color: rgb(0, 0, 0)");

    currentButton_ = buttons[keyboardCounter_];
}

void Keyboard::exit()
{
    currentButton_->setStyleSheet("background-color: rgb(65,65,65); color: rgb(255, 255, 255);");
}

void Keyboard::setRightMove()
{
    keyboardCounter_ = keyboardCounter_ + 1;

    if(keyboardCounter_ >= buttons.size())
    {
        keyboardCounter_ = keyboardCounter_ % buttons.size();
    }

    currentButton_->setStyleSheet("background-color: rgb(65,65,65); color: rgb(255, 255, 255);");

    buttons[keyboardCounter_]->setStyleSheet("background-color: rgb(144,238,144); color: rgb(0, 0, 0)");
    currentButton_ = buttons[keyboardCounter_];
}

void Keyboard::setLeftMove()
{
    keyboardCounter_ = keyboardCounter_ - 1;

    if(keyboardCounter_ < 0)
    {
        keyboardCounter_ += buttons.size();
    }

    currentButton_->setStyleSheet("background-color: rgb(65,65,65); color: rgb(255, 255, 255);");

    buttons[keyboardCounter_]->setStyleSheet("background-color: rgb(144,238,144); color: rgb(0, 0, 0)");
    currentButton_ = buttons[keyboardCounter_];
}

void Keyboard::initializeFont()
{
    QFont font("Arial", 13, QFont::Bold);

    ui->qButton->setFont(font);
    buttons.push_back(ui->qButton);

    ui->wButton->setFont(font);
    buttons.push_back(ui->wButton);

    ui->eButton->setFont(font);
    buttons.push_back(ui->eButton);

    ui->rButton->setFont(font);
    buttons.push_back(ui->rButton);

    ui->tButton->setFont(font);
    buttons.push_back(ui->tButton);

    ui->yButton->setFont(font);
    buttons.push_back(ui->yButton);

    ui->uButton->setFont(font);
    buttons.push_back(ui->uButton);

    ui->iButton->setFont(font);
    buttons.push_back(ui->iButton);

    ui->oButton->setFont(font);
    buttons.push_back(ui->oButton);

    ui->pButton->setFont(font);
    buttons.push_back(ui->pButton);

    ui->bpButton->setFont(font);
    ui->bpButton->setIcon((QIcon("/home/hubert/Documents/Programowanie/AHRS/src/ui/gui/images/keyboard/backspace.png")));
    ui->bpButton->setIconSize(QSize(65, 65));
    buttons.push_back(ui->bpButton);

    ui->aButton->setFont(font);
    buttons.push_back(ui->aButton);

    ui->sButton->setFont(font);
    buttons.push_back(ui->sButton);

    ui->dButton->setFont(font);
    buttons.push_back(ui->dButton);

    ui->fButton->setFont(font);
    buttons.push_back(ui->fButton);

    ui->gButton->setFont(font);
    buttons.push_back(ui->gButton);

    ui->hButton->setFont(font);
    buttons.push_back(ui->hButton);

    ui->jButton->setFont(font);
    buttons.push_back(ui->jButton);

    ui->kButton->setFont(font);
    buttons.push_back(ui->kButton);

    ui->lButton->setFont(font);
    buttons.push_back(ui->lButton);

    ui->apostropheButton->setFont(font);
    buttons.push_back(ui->apostropheButton);

    ui->enterButton->setFont(font);
    buttons.push_back(ui->enterButton);

    ui->numButton_1->setFont(font);
    buttons.push_back(ui->numButton_1);

    ui->zButton->setFont(font);
    buttons.push_back(ui->zButton);

    ui->xButton->setFont(font);
    buttons.push_back(ui->xButton);

    ui->cButton->setFont(font);
    buttons.push_back(ui->cButton);

    ui->vButton->setFont(font);
    buttons.push_back(ui->vButton);

    ui->bButton->setFont(font);
    buttons.push_back(ui->bButton);

    ui->nButton->setFont(font);
    buttons.push_back(ui->nButton);

    ui->mButton->setFont(font);
    buttons.push_back(ui->mButton);

    ui->commaButton->setFont(font);
    buttons.push_back(ui->commaButton);

    ui->dotButton->setFont(font);
    buttons.push_back(ui->dotButton);

    ui->questionButton->setFont(font);
    buttons.push_back(ui->questionButton);

    ui->numButton_5->setFont(font);
    buttons.push_back(ui->numButton_5);

    ui->numButton_2->setFont(font);
    buttons.push_back(ui->numButton_2);

    ui->numButton_3->setFont(font);
    buttons.push_back(ui->numButton_3);

    ui->spaceButton->setFont(font);
    buttons.push_back(ui->spaceButton);

    ui->numButton_7->setFont(font);
    buttons.push_back(ui->numButton_7);

    ui->numButton_6->setFont(font);
    buttons.push_back(ui->numButton_6);
}

void Keyboard::initializeSlots()
{
//    connect ( ui->aButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->bButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->cButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->dButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->eButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->fButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->gButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->hButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->iButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->jButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->kButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->lButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->mButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->nButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->oButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->pButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->qButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->rButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->sButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->tButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->uButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->vButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->wButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->xButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->yButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->zButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->bpButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->numButton_1, SIGNAL( clicked() ), this, SLOT(symbolChange()) );
//    connect ( ui->numButton_2, SIGNAL( clicked() ), this, SLOT(symbolChange()) );
//    connect( ui->numButton_5,SIGNAL(clicked()),this,SLOT(boardchange()));
//    connect( ui->numButton_6,SIGNAL(clicked()),this,SLOT(boardchange()));
//    connect ( ui->numButton_7, SIGNAL( clicked() ), this, SLOT(keyclose()) );
//    connect ( ui->spaceButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
//    connect ( ui->enterButton, SIGNAL( clicked() ), this, SLOT(keyclose()) );
//    connect ( ui->apostropheButton, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );
//    connect ( ui->commaButton, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );
//    connect ( ui->questionButton, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );

}

void Keyboard::setChar()
{
    std::string name = currentButton_->text().toStdString();
    charCallback_(name);
}

void Keyboard::keypadHandler()
{
    const auto currentTime = std::chrono::system_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime_).count();

    previousTime_ = currentTime;

    if(duration > 200 )
    {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        std::string name = button->text().toStdString();
        charCallback_(name);
    }
}

void Keyboard::symbolChange()
{

}

void Keyboard::keyclose()
{

}

void Keyboard::boardchange()
{

}

void Keyboard::lineEditClicked()
{

}
