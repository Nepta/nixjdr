#ifndef CANVASEVENTHANDLER_H
#define CANVASEVENTHANDLER_H

#include <QEvent>
#include <QPixmap>
#include <QObject>
#include <QListWidgetItem>

class CanvasEventHandler : public QObject
{
    Q_OBJECT

signals:
    void addSprite(QPixmap* sprite, int x, int y, int z);

public:
    CanvasEventHandler();
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void setSpritePath(QListWidgetItem *sprite);

private:
    QString m_spritePath;
};

#endif // CANVASEVENTHANDLER_H
