#include "Network/TurnMenuCodes.h"
#include "TurnMenu.h"
#include "ui_TurnMenu.h"

#include <QList>

TurnMenu::TurnMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TurnMenu)
{
    ui->setupUi(this);

    connect(ui->m_TurnList, SIGNAL(updatedTurnList(QString)), this, SLOT(sendUpdatedTurnList(QString)));
}

TurnMenu::~TurnMenu()
{
    delete ui;
}

TurnList *TurnMenu::getTurnList(){
    return ui->m_TurnList;
}

void TurnMenu::on_addItemEdit_returnPressed()
{
    if (!ui->addItemEdit->text().isEmpty()) {
        ui->m_TurnList->addQStringAsItem(QString("%1").arg(ui->addItemEdit->text()));
        ui->addItemEdit->clear();
        ui->addItemEdit->setFocus();
    }
}

void TurnMenu::on_addButton_clicked()
{
    on_addItemEdit_returnPressed();
}

void TurnMenu::on_nextButton_clicked()
{
    ui->m_TurnList->selectNextItem();
}

void TurnMenu::on_deleteButton_clicked()
{
    ui->m_TurnList->deleteCurrentItems();
}

/**
 * @brief TurnMenu::setTurnList Replace the turnList with the given items.
 * @param turnItems
 */
void TurnMenu::setTurnList(QStringList turnItems) {
    ui->m_TurnList->clear();

    for (QString turnItem : turnItems) {
        ui->m_TurnList->addQStringAsItem(turnItem, false);
    }
}

/**
 * @brief TurnMenu::sendUpdatedTurnList Sends the updated TurnList to all the clients.
 * @param turnListItems
 */
void TurnMenu::sendUpdatedTurnList(const QString& turnListItems) {
    QString msg = QString("%1").arg(turnListItems);
    m_SenderClient->sendMessageToServer(msg, (quint16) TurnMenuCodes::UPDATE_TURN);
}
