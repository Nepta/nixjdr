#include "TurnMenu.h"
#include "ui_TurnMenu.h"

#include <QList>

TurnMenu::TurnMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TurnMenu)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes.push_back(60);
    sizes.push_back(1000);
    ui->splitter->setSizes(sizes);

    m_turnList = new TurnList();
    m_turnList->setMaximumHeight(100);
    ui->listLayout->addWidget(m_turnList);
}

TurnMenu::~TurnMenu()
{
    delete ui;
    delete m_turnList;
}

void TurnMenu::on_addItemEdit_returnPressed()
{
    if (!ui->addItemEdit->text().isEmpty()) {
        m_turnList->addQStringAsItem(QString(" %1 ").arg(ui->addItemEdit->text()));
        ui->addItemEdit->clear();
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
