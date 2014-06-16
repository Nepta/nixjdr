#include "Logger.h"
#include <QDebug>
#include "Network/Serializable/Message.h"
#include "MapLog.h"

Logger::Logger(LogGui *gui){
	setGui(gui);
}

void Logger::setGui(LogGui *gui){
	gui_ = gui;
}

void Logger::insertRoute(TargetCode targetCode, Receiver *receiver){
	m_Nodes.insert(targetCode, receiver);
}

Log* Logger::pop(){
	return logStack_.pop();
}

void Logger::push(Log *log){
	logStack_.push(log);
	gui_->pushLog(log->toString());
}

LogGui *Logger::getGui(){
	return gui_;
}

void Logger::processNewData(Header header, QByteArray &data){
	Receiver *receiver = switchNewMessage(header, data);
	Log *log = nullptr;
	if(receiver->isLoggable()){
		TargetCode target = (TargetCode)header.getTarget();
		switch(target){
			case TargetCode::MAP_SERVER:
				log = new MapLog(*receiver);
				break;

			default:
				break;
		}
	}

	if(log){
		log->setMessage(data);
		log->setHeader(header);
		push(log);
        //qDebug() << log->toString();
	}
}
