#include "mycanvas.h"

#include <iostream>
#include <string>
#include <QDir>

MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
{
}

void MyCanvas::OnInit()
{
    myImage.loadFromFile("img/suwako.png");

    // On paramètre le sprite
    mySprite.setTexture(myImage);
    mySprite.setOrigin(0.f,0.f);
    QPushButton *bouton1 = new QPushButton("Bonjour");
}

void MyCanvas::OnUpdate()
{
    // On efface l'écran
    this->clear(sf::Color(0, 128, 0));

    // Une petite rotation du sprite
    mySprite.setRotation(360.f);

    // Et on l'affiche
    this->draw(mySprite);
}
