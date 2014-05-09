#ifndef MAP_H
#define MAP_H

#include "Canvas.h"
#include "SpriteList.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <QListWidget>

class Map : public Canvas{
	Q_OBJECT
	sf::Clock clock_;
	sf::Texture image_;
//    sf::Texture tokenTextureToLoad_;
	sf::Sprite sprite_;

	SpriteList spriteList_;

	int tileHeight_;
	int tileWidth_;
	int nbTilesX_;
	int nbTilesY_;

public:
	Map(QWidget* Parent, const QPoint& Position, const QSize& Size);
	Map* setMap(QString path);
	void onInit();
	void onUpdate();
	void mouseReleaseEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);

private:
	void drawList();

private slots:
    void changeToken(QListWidgetItem*item);

};
#endif // MAP_H
