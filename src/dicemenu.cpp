#include <QMouseEvent>
#include "dicemenu.h"
#include "ui_dicemenu.h"

DiceMenu::DiceMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiceMenu)
{
    ui->setupUi(this);
    DiceMenu::fillDiceButtonList();
    connect(this, SIGNAL(rightClickDiceButton(QPushButton*,bool)),
            this, SLOT(modifyButton(QPushButton*, bool)));
}

DiceMenu::~DiceMenu()
{
    delete ui;
}

bool DiceMenu::eventFilter(QObject *obj, QEvent *event){
    if(event->type()==QEvent::MouseButtonPress || event->type()==QEvent::Wheel){
        if(static_cast<QMouseEvent*>(event)->button()==Qt::LeftButton ||
                static_cast<QWheelEvent*>(event)->delta() > 0){
            emit rightClickDiceButton(m_DiceButtonList.at(m_DiceButtonList.indexOf((QPushButton*)(obj))),true);
        }
        else if(static_cast<QMouseEvent*>(event)->button()==Qt::RightButton ||
                static_cast<QWheelEvent*>(event)->delta() < 0){
            emit rightClickDiceButton(m_DiceButtonList.at(m_DiceButtonList.indexOf((QPushButton*)(obj))),false);
        }
        else{
            return false;
        }
        return true;
    }
    else{
        return false;
    }
}

void DiceMenu::fillDiceButtonList(){
    QHBoxLayout *layout = ui->diceButtonLayout;
    QPushButton *currentButton;
    for(int i=0; i<layout->count(); i++){
        currentButton = dynamic_cast<QPushButton*>(layout->itemAt(i)->widget());
        m_DiceButtonList.append(currentButton);
        currentButton->installEventFilter(this);
    }
}

void DiceMenu::on_cancelButton_clicked(){
    for(int i=0; i<m_DiceButtonList.length() ; i++){
        m_DiceButtonList.at(i)->setText(m_DiceButtonList.at(i)->text().replace(0, m_DiceButtonList.at(i)->text().indexOf("d"), ""));
    }
}

void DiceMenu::on_publicRollButton_clicked(){
    QString message = diceToRoll();
    if(message ==""){
        emit rollDice("<em>Veuillez sélectionner des dés</em>");
    }
    else {
        emit rollDice("/roll " + message);
    }
}


void DiceMenu::on_privateRollButton_clicked(){
    //TODO passer en whisp
    emit rollDice("/roll ");
}

QString DiceMenu::diceToRoll(){
    QString message;
    for(int i=0; i<m_DiceButtonList.length() ; i++){
        if(m_DiceButtonList.at(i)->text().at(0)  !='d'){
            message += m_DiceButtonList.at(i)->text() +"+";
        }
    }

    message.chop(1); //removes the last '+'
    return message;
}

void DiceMenu::modifyButton(QPushButton *buttonToModify, bool actionToExecute){
    int diceCount, indexOfDiceSeparator;
    QString buttonText;

    buttonText = buttonToModify->text();
    indexOfDiceSeparator = buttonText.indexOf("d");
    diceCount = buttonText.left(indexOfDiceSeparator).toInt();

    buttonText.replace(0, indexOfDiceSeparator, "");
    if(actionToExecute){
        diceCount++;
    }
    else if(diceCount!=0){
        diceCount --;
    }
    buttonToModify->setText(buttonText.prepend(QString::number(diceCount)));
}
