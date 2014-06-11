#include "Character.h"
#include "GameObjectDialog.h"
#include "ui_GameObjectDialog.h"

GameObjectDialog::GameObjectDialog(GameObject *object, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameObjectDialog)
{
    ui->setupUi(this);
}

GameObjectDialog::~GameObjectDialog()
{
    delete ui;
}


void GameObjectDialog::on_createButton_clicked()
{
    QString name = ui->m_NameEdit->text();
    int hp = ui->m_HpEdit->value();

    m_Object = new Character(name, hp, hp);

    close();
}
