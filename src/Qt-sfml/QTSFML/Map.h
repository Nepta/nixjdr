#ifndef MAP_H
#define MAP_H

#include "QTSFMLCanvas.h"
#include <SFML/Graphics.hpp>

class Map : public QSFMLCanvas
{
public:
    Map(QWidget* Parent, const QPoint& Position, const QSize& Size);
    void OnInit();
    void OnUpdate();

private:
    sf::Clock clock_;
    sf::Texture image_;
    sf::Sprite sprite_;
    int tileHeight_;
    int tileWidth_;
    int nbTilesX_;
    int nbTilesY_;
};

#endif // MAP_H
