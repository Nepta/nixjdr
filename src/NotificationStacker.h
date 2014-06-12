#ifndef NOTIFICATIONSTACKER_H
#define NOTIFICATIONSTACKER_H

#include <QList>
#include <QTimer>

#include "Tooltip.h"

class NotificationStacker : public QObject
{
    Q_OBJECT

public:
    NotificationStacker();
    ~NotificationStacker();

private:
    QList<Tooltip*> m_Stack;
    int m_Size;

    void timerEvent(QTimerEvent *event);

public slots:
    void pushNotification();
};

#endif // NOTIFICATIONSTACKER_H
