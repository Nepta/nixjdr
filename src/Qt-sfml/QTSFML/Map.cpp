#include "Map.h"

#include <iostream>
#include <string>
#include <QDir>
#include <QDebug>
#include <QMouseEvent>

Map::Map(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
{
}

void Map::OnInit()
{
    image_.loadFromFile("resource/littleForest.png");

    // Dimensions d'une tile
    tileHeight_ = 32;
    tileWidth_ = 32;

    // Nombre de tiles en longueur et largeur
    nbTilesX_ = 25;
    nbTilesY_ = 19;

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

    // Dessine les axes verticaux de la grille
    for(int i = 0; i < nbTilesX_; i++){
        sf::Vertex line[]={
            sf::Vertex(sf::Vector2f(i*tileWidth_, 0)),
            sf::Vertex(sf::Vector2f(i*tileWidth_, 600))
        };
        this->draw(line, 25, sf::Lines);
    }

    // Dessine les axes horizontaux de la grille
    for(int i = 0; i < nbTilesY_; i++){
        sf::Vertex line[]={
            sf::Vertex(sf::Vector2f(0, i*tileHeight_)),
            sf::Vertex(sf::Vector2f(800, i*tileHeight_))
        };
        this->draw(line, 2, sf::Lines);
    }

    clock_.restart();
}