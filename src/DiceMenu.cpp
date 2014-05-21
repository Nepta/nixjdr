#include <QMouseEvent>
#include "DiceMenu.h"
#include "ui_DiceMenu.h"

DiceMenu::DiceMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiceMenu)
{
    ui->setupUi(this);
    DiceMenu::fillDiceButtonList();
    foreach(QPushButton* button, m_DiceButtonList) {
        button->setMinimumSize(50,5);
    }
    connect(this, SIGNAL(rightClickDiceButton(QPushButton*,bool)),
        this, SLOT(modifyButton(QPushButton*, bool)));
}

DiceMenu::~DiceMenu()
{
    delete ui;
}

bool DiceMenu::eventFilter(QObject *obj, QEvent *event){
    bool eventHandled = false;

    if(event->type()==QEvent::MouseButtonPress || event->type()==QEvent::Wheel) {
        Qt::MouseButton mouseButton = static_cast<QMouseEvent*>(event)->button();
        int delta = static_cast<QWheelEvent*>(event)->delta();

        if(mouseButton == Qt::RightButton || delta < 0) {
            emit rightClickDiceButton((QPushButton*) obj, false);
            eventHandled = true;
        }
        else if(mouseButton == Qt::LeftButton || delta > 0) {
            emit rightClickDiceButton((QPushButton*) obj, true);
            eventHandled = true;
        }
    }

    return eventHandled;
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
    foreach(QPushButton* button, m_DiceButtonList) {
        QString buttonText = button->text();
        if(buttonText.contains("d")){
            buttonText.replace(0, buttonText.indexOf("d"), "");
        }
        else{
            buttonText.setNum(0);
        }
        button->setText(buttonText);
    }
}

void DiceMenu::on_publicRollButton_clicked(){
    QString message = diceToRoll();

    emit rollDice(message, false);
}


void DiceMenu::on_privateRollButton_clicked(){
    QString message = diceToRoll();

    emit rollDice(message, true);
}

QString DiceMenu::diceToRoll(){
    QString message;

    foreach(QPushButton *button, m_DiceButtonList) {
        QString buttonText = button->text();
        if (buttonText.at(0) != 'd') {
            if(buttonText.at(0) == '-'){
                message += '-' + buttonText ;
            }
            else{
                message += '+' + buttonText;
            }
        }
    }

    return message;
}

void DiceMenu::modifyButton(QPushButton *buttonToModify, bool actionToExecute){
    int diceCount, indexOfDiceSeparator;
    QString buttonText;

    buttonText = buttonToModify->text();
    if(buttonText.contains("d")){
        indexOfDiceSeparator = buttonText.indexOf("d");
    }
    else{
        indexOfDiceSeparator = buttonText.length();
    }
    diceCount = buttonText.left(indexOfDiceSeparator).toInt();

    buttonText.replace(0, indexOfDiceSeparator, "");
    if(actionToExecute){
        diceCount++;
    }
    else {
        diceCount --;
    }
    buttonToModify->setText(buttonText.prepend(QString::number(diceCount)));
}


void DiceMenu::requestRoll(QString &msg){
    msg = QString("/roll %1").arg(diceToRoll());
}
