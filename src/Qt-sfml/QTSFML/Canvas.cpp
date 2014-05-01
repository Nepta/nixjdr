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
    image_.loadFromFile("img/suwako.png");

    // On paramètre le sprite
    sprite_.setTexture(image_);
    sprite_.setOrigin(0.f,0.f);

    clock_.restart();
}

void Canvas::OnUpdate()
{
    // On efface l'écran
    this->clear(sf::Color(0, 128, 0));

    // Une petite rotation du sprite
    sprite_.setRotation(clock_.getElapsedTime().asSeconds() * 50.f);

    // Et on l'affiche
    this->draw(sprite_);
    clock_.restart();
}
