#include "Canvas.h"
#include "Action.h"
#include "CoutAction.h"
#include "ActionChooser.h"
#include "SpriteList.h"

#include <iostream>
#include <string>
#include <QDir>
#include <QDebug>
#include <QMouseEvent>

Canvas::Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
	QSFMLCanvas(Parent, Position, Size){
}

void Canvas::OnInit(){
	image_.loadFromFile("resource/resize_suwako.png");
	SpriteList::instance().newTexture(image_);
	SpriteList::instance().addSprite(0,0);
	
//	// On paramètre le sprite
//	sprite_.setTexture(image_);
//	sprite_.setOrigin(0.f,0.f);
//	
//	std::vector<sf::Sprite>& sprite = *new std::vector<sf::Sprite>();
//	sprite.push_back(sprite_);
//	spriteList_.push_back({image_, sprite});
//	
	
	setMouseTracking(true);
	clock_.restart();
}

void Canvas::OnUpdate(){
	// On efface l'écran
	clear();

	// Et on l'affiche
//	draw(sprite_);
	drawList();
	clock_.restart();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event){
	int&& x = event->x();
	int&& y = event->y();
	Action& action = ActionChooser::instance().choose(x,y);
	action.execute();
	delete &action;
}

void Canvas::drawList(){
	for(auto &texturedSprite : SpriteList::instance().list_){ //R.A.C.H.E.
		for(auto &sprite : texturedSprite.second){
			draw(sprite);
		}
	}
}
