#include "Map.h"
#include "Action.h"
#include "TokenNoAction.h"
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

void Map::onInit(){
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

//	sf::Texture texture;
//	texture.loadFromFile("resource/cirno.png");
//	spriteList_.newTexture(texture);

    tokenTextureToLoad_.loadFromFile("resource/cirno.png");
    spriteList_.newTexture(tokenTextureToLoad_);

    clock_.restart();
}

void Map::onUpdate()
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
	 for(auto &texturedSprite : spriteList_.list_){
        for(auto &sprite : texturedSprite.second){
            draw(sprite);
        }
    }
}

void Map::changeToken(QListWidgetItem * item)
{
    QString textSprite;
    textSprite = QString("resource/")+item->text()+QString(".png");
    qDebug() << textSprite;
    tokenTextureToLoad_.loadFromFile(textSprite.toStdString());
	 spriteList_.newTexture(tokenTextureToLoad_);
}

void Map::mouseReleaseEvent(QMouseEvent *event){
	int&& x = event->x();
	int&& y = event->y();


	// Pour obtenir l'origine de la case sur laquelle afficher
	x = x/tileWidth_;
	x = x*tileWidth_;

	y = y/tileHeight_;
	y = y*tileHeight_;

	Action& action = ActionChooser::instance().choose(x,y,spriteList_);
	action.execute();
	delete &action;
}

void Map::mousePressEvent(QMouseEvent *event){
	int x = event->x()/tileWidth_*tileWidth_;
	int y = event->y()/tileHeight_*tileHeight_;
	sf::Sprite *selectedSprite = spriteList_.searchSprite(x,y);
	ActionChooser::instance().selectSprite(selectedSprite);
}

void Map::mouseMoveEvent(QMouseEvent *event){
    ActionChooser::instance().isMoving(true);
	int x = event->x();
	int y = event->y();
	Action& action = ActionChooser::instance().choose(x,y,spriteList_);
	action.execute();
	delete &action;
    ActionChooser::instance().isMoving(false);
}
