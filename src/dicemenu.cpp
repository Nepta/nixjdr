#include "dicemenu.h"
#include "ui_dicemenu.h"

//#include <QMouseEvent>

DiceMenu::DiceMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiceMenu)
{
    //TODO check segfault
    ui->setupUi(this);
}

DiceMenu::~DiceMenu()
{
    delete ui;
}

void DiceMenu::on_diceFourButton_clicked(){
    addDiceToRoll(4);
}
void DiceMenu::on_diceSixButton_clicked(){
    addDiceToRoll(6);
}
void DiceMenu::on_diceEightButton_clicked(){
    addDiceToRoll(8);
}
void DiceMenu::on_diceTenButton_clicked(){
    addDiceToRoll(10);
}
void DiceMenu::on_diceTwelveButton_clicked(){
    addDiceToRoll(12);
}
void DiceMenu::on_diceSixteenButton_clicked(){
    addDiceToRoll(16);
}
void DiceMenu::on_diceTwentyButton_clicked(){
    addDiceToRoll(20);
}



void DiceMenu::on_publicRollButton_clicked(){
    emit rollDice("/roll " + m_dicesToRoll);
}


void DiceMenu::on_privateRollButton_clicked(){
    //TODO passer en whisp
    emit rollDice("/roll " + m_dicesToRoll);
}

void DiceMenu::addDiceToRoll(int diceType){
    m_dicesToRoll = "1d" + QString::number(diceType);
}


/*
 * Pour passer en fenetre sans bordure deplacable
void DiceMenu::mousePressEvent(QMouseEvent *evt){
    //QWidget::mousePressEvent(evt);

    m_oldPos = evt->globalPos();
}

void DiceMenu::mouseMoveEvent(QMouseEvent *evt){
    //QWidget::mouseMoveEvent(evt);

    const QPoint delta = evt->globalPos() - m_oldPos;
    move(x()+delta.x(), y()+delta.y());
    m_oldPos = evt->globalPos();
}
*/
