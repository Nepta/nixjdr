#include "tokenmenu.h"
#include "ui_tokenmenu.h"
#include <QDebug>

TokenMenu::TokenMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TokenMenu)
{
    ui->setupUi(this);

    ui->listToken->insertItem(0, new QListWidgetItem(
        QIcon("resource/flandre.png"), "flandre"));
    ui->listToken->insertItem(1, new QListWidgetItem(
        QIcon("resource/cirno.png"), "cirno"));
    ui->listToken->insertItem(2, new QListWidgetItem(
        QIcon("resource/sakuya.png"), "sakuya"));
    ui->listToken->insertItem(3, new QListWidgetItem(
        QIcon("resource/marisa.png"), "marisa"));
    ui->listToken->insertItem(4, new QListWidgetItem(
        QIcon("resource/rumia.png"), "rumia"));
    ui->listToken->insertItem(5, new QListWidgetItem(
        QIcon("resource/reimu.png"), "reimu"));
    ui->listToken->insertItem(6, new QListWidgetItem(
        QIcon("resource/patchouli.png"), "patchouli"));
    ui->listToken->insertItem(7, new QListWidgetItem(
        QIcon("resource/youmu.png"), "youmu"));
    ui->listToken->insertItem(8, new QListWidgetItem(
        QIcon("resource/remilia.png"), "remilia"));
    ui->listToken->insertItem(9, new QListWidgetItem(
        QIcon("resource/yuyuko.png"), "yuyuko"));
    ui->listToken->insertItem(10, new QListWidgetItem(
        QIcon("resource/sanae.png"), "sanae"));
    ui->listToken->insertItem(11, new QListWidgetItem(
        QIcon("resource/aya.png"), "aya"));

}

TokenMenu::~TokenMenu()
{
    delete ui;
}

Ui::TokenMenu *TokenMenu::getUi() {
    return ui;
}

void TokenMenu::on_researchButton_clicked()
{
    qDebug() << "ALERT";
}
