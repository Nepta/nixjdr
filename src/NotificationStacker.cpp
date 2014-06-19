#include "NotificationStacker.h"

NotificationStacker::NotificationStacker(){
    m_Size = 0;
}

NotificationStacker::~NotificationStacker(){}

void NotificationStacker::setParent(QWidget *parent){
    m_Parent = parent;
}

void NotificationStacker::pushNotification(QString text){
    m_Size++;
    Tooltip* notif = new Tooltip();
    notif->setParent(m_Parent);
    notif->pushInfo(text);
    notif->showTooltip(QPoint(Tooltip::NOTIFICATION_OFFSET_X,
                              Tooltip::NOTIFICATION_OFFSET_Y + (m_Size-1)*30));
    notif->raise();
    m_Stack << notif;
    if(m_Size == 1){
        m_Timer = this->startTimer(TIMER_INTERVAL);
    }
}

void NotificationStacker::timerEvent(QTimerEvent *event){
    if(!m_Stack.isEmpty()){
        m_LastNotif = m_Stack.takeFirst();
        m_Size--;
        m_LastNotif->hide();
        updatePosition();
        if(m_Size == 0){
            this->killTimer(m_Timer);
        }
    }
}

void NotificationStacker::updatePosition()
{
    for(int i = 0; i < m_Size; i++){
        m_Stack.at(i)->move(QPoint(Tooltip::NOTIFICATION_OFFSET_X,
                                   Tooltip::NOTIFICATION_OFFSET_Y + i*30));
    }
}
