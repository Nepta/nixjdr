#include "Canvas.h"

#include <iostream>
#include <string>
#include <QDir>

Canvas::Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
{
}

void Canvas::OnInit()
{
    myImage.loadFromFile("img/suwako.png");

    // On paramètre le sprite
    mySprite.setTexture(myImage);
    mySprite.setOrigin(0.f,0.f);
}

void Canvas::OnUpdate()
{
    // On efface l'écran
    this->clear(sf::Color(0, 128, 0));

    // Une petite rotation du sprite
    mySprite.setRotation(360.f);

    // Et on l'affiche
    this->draw(mySprite);
}
