#include "Character.h"
#include "StyleSheet.h"
#include "GameObjectDialog.h"
#include "ui_GameObjectDialog.h"

/**
 * @brief GameObjectDialog::GameObjectDialog Open a window to create a new GameObject.
 * @param parent
 */
GameObjectDialog::GameObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameObjectDialog)
{
    ui->setupUi(this);
    setStyleSheet(StyleSheet::s_StyleSheet);
    m_EditMode = false;
}

/**
 * @brief GameObjectDialog::GameObjectDialog Open a window to edit an already existing GameObject.
 * @param gameObject GameObject to edit.
 * @param parent
 */
GameObjectDialog::GameObjectDialog(GameObject *gameObject, QWidget *parent) :
    GameObjectDialog(parent)
{
    m_EditMode = true;

    Character *character = dynamic_cast<Character*>(gameObject);
    m_Object = character;
    ui->m_HpMaxEdit->setValue(character->getMaxHp());
    ui->m_HpEdit->setValue(character->getHp());

    ui->m_NameEdit->setText(character->getName());
    ui->m_NameEdit->setEnabled(false);

    ui->createButton->setText(tr("Editer"));
}

GameObjectDialog::~GameObjectDialog()
{
    delete ui;
}

void GameObjectDialog::on_createButton_clicked() {
    QString name = ui->m_NameEdit->text();
    int maxHp = ui->m_HpMaxEdit->value();
    int hp = ui->m_HpEdit->value();

    if (m_EditMode) {
        Character *character = dynamic_cast<Character*>(m_Object);
        character->setMaxHp(maxHp);
        character->setHp(hp);
    }
    else {
        m_Object = new Character(name, maxHp, hp);
    }

    accept();
}

GameObject *GameObjectDialog::getGameObject() {
    return m_Object;
}