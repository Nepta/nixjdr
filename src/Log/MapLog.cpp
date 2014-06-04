#include "MapLog.h"

MapLog::MapLog(Receiver& receiver) : Log(receiver){}

QString MapLog::toString(){
	QString logMessage;
	switch(getHeader().getCode()){
		case 1:
			logMessage = "addSpriteAction(" + getMessage().getString() + ")";
			break;

		case 2:
			logMessage = "removeSpriteAction(" + getMessage().getString() + ")";
			break;

		case 3:
			logMessage = "removeAllFoWAction(" + getMessage().getString() + ")";
			break;

		default:
			break;
	}
 return logMessage;
}
