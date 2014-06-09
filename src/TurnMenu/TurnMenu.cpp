#include "Network/TurnMenuCodes.h"
#include "TurnMenu.h"
#include "ui_TurnMenu.h"

#include <QList>

TurnMenu::TurnMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TurnMenu)
{
    ui->setupUi(this);

    QList<int> sizes = {60, 600, 300};
    ui->splitter->setSizes(sizes);

    m_turnList = new TurnList();
    m_turnList->setMaximumHeight(100);
    ui->listLayout->addWidget(m_turnList);

    connect(m_turnList, SIGNAL(updatedTurnList(QString)), this, SLOT(sendUpdatedTurnList(QString)));
}

TurnMenu::~TurnMenu()
{
    delete ui;
    delete m_turnList;
}

TurnList *TurnMenu::getTurnList(){
    return m_turnList;
}

void TurnMenu::on_addItemEdit_returnPressed()
{
    if (!ui->addItemEdit->text().isEmpty()) {
        m_turnList->addQStringAsItem(QString("%1").arg(ui->addItemEdit->text()));
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
    m_turnList->selectNextItem();
}

void TurnMenu::on_deleteButton_clicked()
{
    m_turnList->deleteCurrentItems();
}

/**
 * @brief TurnMenu::setTurnList Replace the turnList with the given items.
 * @param turnItems
 */
void TurnMenu::setTurnList(QStringList turnItems) {
    m_turnList->clear();

    for (QString turnItem : turnItems) {
        m_turnList->addQStringAsItem(turnItem, false);
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

QWidget* TurnMenu::getDiceWidget(){
    return ui->diceMenuWidget;
}
