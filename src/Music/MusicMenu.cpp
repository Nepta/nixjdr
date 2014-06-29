#include "MusicMenu.h"
#include "ui_MusicMenu.h"

MusicMenu::MusicMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicMenu)
{
    ui->setupUi(this);
}

MusicMenu::~MusicMenu()
{
    delete ui;
}
