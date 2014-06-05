#include "MapLog.h"
#include "Database/Repository/RepositoryManager.h"
#include "Token/TokenItem.h"

MapLog::MapLog(Receiver& receiver) : Log(receiver){}

QString MapLog::toString(){
	QString logMessage;
	QString spriteName = RepositoryManager::s_SpriteRepository.getSpriteName(getMessage().getString().toInt(),db_);
	switch(getHeader().getCode()){
		case 1:
			logMessage = "addSpriteAction(" + spriteName + ")";
			break;

		case 2:
			logMessage = "removeSpriteAction(" + spriteName + ")";
			break;

		case 3:
			logMessage = "removeAllFoWAction(" + spriteName + ")";
			break;

		default:
			break;
	}
 return logMessage;
}
