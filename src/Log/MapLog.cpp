#include "MapLog.h"
#include "Database/Repository/RepositoryManager.h"
#include "Token/TokenItem.h"
#include "Canvas/Network/MapClient.h"

MapLog::MapLog(Receiver& receiver) : Log(receiver){}

QString MapLog::toString(){
	QString logMessage;
    QString spriteName = RepositoryManager::s_SpriteRepository.getSpriteName(
        getMessage().getString().toInt()
    );

	switch((MapCodes) getHeader().getCode()){
		case MapCodes::ADD_SPRITE:
			logMessage = "addSpriteAction(" + spriteName + ")";
			break;

		case MapCodes::REMOVE_SPRITE:
			logMessage = "removeSpriteAction(" + spriteName + ")";
			break;

		case MapCodes::REMOVE_ALL_FOW:
			logMessage = "removeAllFoWAction(" + spriteName + ")";
			break;

		default:
			break;
	}
 return logMessage;
}
