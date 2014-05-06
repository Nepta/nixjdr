#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>
#include <QMdiSubWindow>

class Canvas : public QMdiSubWindow, public sf::RenderWindow
{
public :

    Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size,
        unsigned int FrameTime = 0);
    virtual ~Canvas();

private :

    virtual void OnInit();
    virtual void OnUpdate();
    virtual QPaintEngine* paintEngine() const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

#endif // CANVAS_H
