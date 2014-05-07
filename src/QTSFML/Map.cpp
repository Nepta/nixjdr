#include "Map.h"
#include "Action.h"
#include "CoutAction.h"
#include "ActionChooser.h"
#include "SpriteList.h"

#include <iostream>
#include <string>
#include <QDir>
#include <QDebug>
#include <QMouseEvent>

Map::Map(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    Canvas(Parent, Position, Size)
{
}

Map* Map::setMap(QString mapPath){
	image_.loadFromFile(mapPath.toStdString());
	return this;
}

void Map::OnInit(){
    // Dimensions d'une tile (a parametrer avec parametres)
    tileHeight_ = 32;
    tileWidth_ = 32;

    // Nombre de tiles en longueur et largeur (a faire en parametre)
    // ou ennfonction de la taille de l'image et des tiles
    nbTilesX_ = 25;
    nbTilesY_ = 19;

    // On paramètre le sprite
    sprite_.setTexture(image_);
    sprite_.setOrigin(0.f,0.f);

    sf::Texture texture;
    texture.loadFromFile("resource/cirno.png");
    SpriteList::instance().newTexture(texture);

    clock_.restart();
}

void Map::OnUpdate()
{
    // On efface l'écran
    this->clear();

    // Dessine map
    this->draw(sprite_);

    // Dessine les elements de la liste
    drawList();

    // Dessine les axes verticaux de la grille
    for(int i = 0; i < nbTilesX_; i++){
        sf::Vertex line[]={
            sf::Vertex(sf::Vector2f(i*tileWidth_, 0)),
            sf::Vertex(sf::Vector2f(i*tileWidth_, image_.getSize().y))
        };
        this->draw(line, 2, sf::Lines);
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
    for(auto &texturedSprite : SpriteList::instance().list_){
        for(auto &sprite : texturedSprite.second){
            draw(sprite);
        }
    }
}

void Map::mouseReleaseEvent(QMouseEvent *event){
    int&& x = event->x();
    int&& y = event->y();


    // Pour obtenir l'origine de la case sur laquelle afficher
    x = x/tileWidth_;
    x = x*tileWidth_;

    y = y/tileHeight_;
    y = y*tileHeight_;

	 Action& action = ActionChooser::instance().choose(x,y);
	 action.execute();
     delete &action;
}

void Map::mousePressEvent(QMouseEvent *event){
    int x = event->x()/tileWidth_*tileWidth_;
	int y = event->y()/tileHeight_*tileHeight_;
    ActionChooser::instance().selectSprite(x,y);
}

void Map::mouseMoveEvent(QMouseEvent *event){
    ActionChooser::instance().isMoving(true);
	int x = event->x();
	int y = event->y();
	Action& action = ActionChooser::instance().choose(x,y);
	action.execute();
	delete &action;
    ActionChooser::instance().isMoving(false);
}
