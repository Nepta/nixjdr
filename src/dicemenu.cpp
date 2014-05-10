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
    bool eventHandled = false;

    if(event->type()==QEvent::MouseButtonPress || event->type()==QEvent::Wheel) {
        Qt::MouseButton mouseButton = static_cast<QMouseEvent*>(event)->button();
        int delta = static_cast<QWheelEvent*>(event)->delta();

        if(mouseButton == Qt::LeftButton || delta > 0) {
            emit rightClickDiceButton((QPushButton*) obj, true);
            eventHandled = true;
        }
        else if(mouseButton == Qt::RightButton || delta < 0) {
            emit rightClickDiceButton((QPushButton*) obj, false);
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
        buttonText.replace(0, buttonText.indexOf("d"), "");

        button->setText(buttonText);
    }
}

void DiceMenu::on_publicRollButton_clicked(){
    QString message = diceToRoll();
    if(message == ""){
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

    foreach(QPushButton *button, m_DiceButtonList) {
        QString buttonText = button->text();
        if (buttonText.at(0) != 'd') {
            message += buttonText + "+";
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
