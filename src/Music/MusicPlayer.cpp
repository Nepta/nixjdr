#include "MusicPlayer.h"
#include "ui_MusicPlayer.h"

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}
