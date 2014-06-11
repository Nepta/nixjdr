#include "NotificationStacker.h"

#include <QDebug>

NotificationStacker::NotificationStacker(){
//    m_Stack.clear();
    m_Size = 0;
    this->startTimer(2000);
}

NotificationStacker::~NotificationStacker(){
//    m_Stack.clear();
}

void NotificationStacker::pushNotification(){
//    Tooltip* notif;
//    notif->setToolTip("text");
//    m_Stack.append(notif);
//    qDebug() << "push";
    m_Size++;
}

void NotificationStacker::timerEvent(QTimerEvent *event){
//    qDebug() << "begin";
//    if(!m_Stack.isEmpty()){
//        qDebug() << "not empty";
//        m_Stack.pop_back();
//        qDebug() << "poped";
//    }
    if(m_Size > 0){
        m_Size--;
        qDebug() << m_Size;
    }
}
