#include "Canvas.h"
#include "Action.h"
#include "CoutAction.h"
#include <iostream>
#include <string>
#include <QDir>
#include <QDebug>
#include <QMouseEvent>

Canvas::Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
{
}

void Canvas::OnInit()
{
    image_.loadFromFile("resource/suwako.png");

    // On paramètre le sprite
    sprite_.setTexture(image_);
    sprite_.setOrigin(0.f,0.f);

    setMouseTracking(true);
    clock_.restart();
}

void Canvas::OnUpdate()
{
    // On efface l'écran
    this->clear(sf::Color(255, 255, 255, 0));

    // Et on l'affiche
    this->draw(sprite_);
    clock_.restart();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event){
	int&& x = event->x();
	int&& y = event->y();
	Action *action = new CoutAction(x,y);
	action->execute();
	delete action;
}
