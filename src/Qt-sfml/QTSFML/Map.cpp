#include "Map.h"

#include <iostream>
#include <string>
#include <QDir>

Map::Map(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
{
}

void Map::OnInit()
{
    image_.loadFromFile("resource/littleForest.png");

    // On paramètre le sprite
    sprite_.setTexture(image_);
    sprite_.setOrigin(0.f,0.f);

    clock_.restart();
}

void Map::OnUpdate()
{
    // On efface l'écran
    this->clear();

    // Et on l'affiche
    this->draw(sprite_);
    clock_.restart();
}
