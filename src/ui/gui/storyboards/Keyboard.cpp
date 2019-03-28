#include "Keyboard.h"
#include "ui_Keyboard.h"

Keyboard::Keyboard(std::function<void(std::string)> callback, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard),
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

void Keyboard::initializeFont()
{
    QFont font("Arial", 13, QFont::Bold);

    ui->aButton->setFont(font);
    ui->bButton->setFont(font);
    ui->cButton->setFont(font);
    ui->dButton->setFont(font);
    ui->eButton->setFont(font);
    ui->fButton->setFont(font);
    ui->gButton->setFont(font);
    ui->hButton->setFont(font);
    ui->iButton->setFont(font);
    ui->jButton->setFont(font);
    ui->kButton->setFont(font);
    ui->lButton->setFont(font);
    ui->mButton->setFont(font);
    ui->nButton->setFont(font);
    ui->oButton->setFont(font);
    ui->pButton->setFont(font);
    ui->qButton->setFont(font);
    ui->rButton->setFont(font);
    ui->sButton->setFont(font);
    ui->tButton->setFont(font);
    ui->uButton->setFont(font);
    ui->vButton->setFont(font);
    ui->wButton->setFont(font);
    ui->xButton->setFont(font);
    ui->yButton->setFont(font);
    ui->zButton->setFont(font);
    ui->bpButton->setFont(font);
    ui->bpButton->setIcon((QIcon("/home/hubert/Documents/Programowanie/AHRS/src/ui/gui/images/keyboard/backspace.png")));
    ui->bpButton->setIconSize(QSize(65, 65));
    ui->numButton_1->setFont(font);
    ui->numButton_2->setFont(font);
    ui->numButton_5->setFont(font);
    ui->numButton_6->setFont(font);
    ui->numButton_7->setFont(font);
    ui->spaceButton->setFont(font);
    ui->enterButton->setFont(font);
    ui->apostropheButton->setFont(font);
    ui->commaButton->setFont(font);
    ui->questionButton->setFont(font);
}

void Keyboard::initializeSlots()
{
    connect ( ui->aButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->bButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->cButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->dButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->eButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->fButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->gButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->hButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->iButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->jButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->kButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->lButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->mButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->nButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->oButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->pButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->qButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->rButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->sButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->tButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->uButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->vButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->wButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->xButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->yButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->zButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->bpButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->numButton_1, SIGNAL( clicked() ), this, SLOT(symbolChange()) );
    connect ( ui->numButton_2, SIGNAL( clicked() ), this, SLOT(symbolChange()) );
    connect( ui->numButton_5,SIGNAL(clicked()),this,SLOT(boardchange()));
    connect( ui->numButton_6,SIGNAL(clicked()),this,SLOT(boardchange()));
    connect ( ui->numButton_7, SIGNAL( clicked() ), this, SLOT(keyclose()) );
    connect ( ui->spaceButton, SIGNAL( clicked() ), this, SLOT( keypadHandler() ) );
    connect ( ui->enterButton, SIGNAL( clicked() ), this, SLOT(keyclose()) );
    connect ( ui->apostropheButton, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );
    connect ( ui->commaButton, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );
    connect ( ui->questionButton, SIGNAL( clicked() ), this, SLOT(keypadHandler()) );

}

void lineEditHandler()
{

}

void Keyboard::keypadHandler()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    std::string name = button->text().toStdString();
    charCallback_(name);
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
