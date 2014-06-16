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

    void setParent(QWidget* parent);

private:
    QList<Tooltip*> m_Stack;
    int m_Timer;
    int m_Size;
    QWidget* m_Parent;
    Tooltip* m_LastNotif;

    void timerEvent(QTimerEvent *event);
    void updatePosition();

public slots:
    void pushNotification();
};

#endif // NOTIFICATIONSTACKER_H
