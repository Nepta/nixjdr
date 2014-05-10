#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>
#include <QMdiSubWindow>

class Canvas : public QMdiSubWindow, public sf::RenderWindow
{
    Q_OBJECT

public :
    Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size,
          unsigned int FrameTime = 16);
    virtual ~Canvas();

protected :
    virtual void onInit() = 0;
    virtual void onUpdate() = 0;

private :
    virtual QPaintEngine* paintEngine() const;
    virtual void showEvent(QShowEvent*);

    QTimer myTimer;
    bool   myInitialized;

private slots:
    void sfmlPaint();
};

#endif // CANVAS_H
