#ifndef MAP_H
#define MAP_H

#include "Canvas.h"
#include "SpriteList.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Map : public Canvas{
	sf::Clock clock_;
	sf::Texture image_;
	sf::Sprite sprite_;

	SpriteList spriteList_;

	int tileHeight_;
	int tileWidth_;
	int nbTilesX_;
	int nbTilesY_;

public:
	Map(QWidget* Parent, const QPoint& Position, const QSize& Size);
	Map* setMap(QString path);
	void OnInit();
	void OnUpdate();
	void mouseReleaseEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);

private:
	void drawList();

};
#endif // MAP_H
