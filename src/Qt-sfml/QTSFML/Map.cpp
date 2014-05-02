#include "Map.h"
#include "Action.h"
#include "CoutAction.h"
#include "ActionChooser.h"

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

    std::vector<sf::Sprite>& sprite = *new std::vector<sf::Sprite>();
    sprite.push_back(sprite_);
    spriteList_.push_back({image_, sprite});
    ActionChooser::instance().spriteList(spriteList_);

    clock_.restart();
}

void Map::OnUpdate()
{
    // On efface l'écran
    this->clear();

    // Et on l'affiche
    drawList();

    // Dessine les axes verticaux de la grille
    for(int i = 0; i < nbTilesX_; i++){
        sf::Vertex line[]={
            sf::Vertex(sf::Vector2f(i*tileWidth_, 0)),
            sf::Vertex(sf::Vector2f(i*tileWidth_, image_.getSize().y))
        };
        this->draw(line, 25, sf::Lines);
    }

    // Dessine les axes horizontaux de la grille
    for(int i = 0; i < nbTilesY_; i++){
        sf::Vertex line[]={
            sf::Vertex(sf::Vector2f(0, i*tileHeight_)),
            sf::Vertex(sf::Vector2f(image_.getSize().x, i*tileHeight_))
        };
        this->draw(line, 2, sf::Lines);
    }

    clock_.restart();
}

void Map::drawList(){
    for(auto &texturedSprite : spriteList_){
        for(auto &sprite : texturedSprite.second){
            draw(sprite);
        }
    }
}