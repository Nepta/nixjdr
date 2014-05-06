#ifndef CANVAS_H
#define CANVAS_H

#include "QTSFMLCanvas.h"
#include <SFML/Graphics.hpp>
#include <QPushButton>
#include <vector>

class Canvas : public QSFMLCanvas{
	sf::Clock clock_;
	sf::Texture image_;
	sf::Sprite sprite_;

private:
	void drawList();

public:
    Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size);
    void OnInit();
    void OnUpdate();
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CANVAS_H
