#ifndef CANVAS_H
#define CANVAS_H

#include "QTSFMLCanvas.h"
#include <SFML/Graphics.hpp>
#include <QPushButton>

class Canvas : public QSFMLCanvas
{
public:
    Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size);
    void OnInit();
    void OnUpdate();
    void mouseReleaseEvent(QMouseEvent *event);

private:
    sf::Clock clock_;
    sf::Texture image_;
    sf::Sprite sprite_;
};

#endif // CANVAS_H
