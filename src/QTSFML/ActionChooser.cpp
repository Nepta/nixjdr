#include "ActionChooser.h"
#include "TokenNoAction.h"
#include "TokenAddAction.h"
#include "TokenDelAction.h"
#include "TokenMoveAction.h"
#include "SpriteList.h"
#include <QDebug>

ActionChooser& ActionChooser::instance(){
	static ActionChooser *instance = new ActionChooser();
	return *instance;
}

void ActionChooser::selectSprite(sf::Sprite* selectedSprite){
	selectedSprite_ = selectedSprite;
}

void ActionChooser::isMoving(bool state){
	isMovementAnimation_ = state;
}

ActionChooser::ActionType ActionChooser::selectAction(sf::Sprite *sprite){
	void* hasSprite = sprite;
    ActionType type = None;
	
	if(!selectedSprite_ && !hasSprite && !isMovementAnimation_){
		type = Add;
	}
	else if(selectedSprite_ && (!hasSprite || isMovementAnimation_)){
		type = Move;
	}
	else if(hasSprite){
		type = Remove;
	}
	else{
        type = None;
	}
	
	return type;
}

Action& ActionChooser::choose(int x, int y, SpriteList& spriteList){
	Action *action;
	sf::Sprite *hasSprite = spriteList.searchSprite(x,y);
	ActionType type(selectAction(hasSprite));
	switch(type){
        case None:
            action = new TokenNoAction(x,y);
			break;

		case Add:
			action = new TokenAddAction(x,y,spriteList);
			break;

		case Remove:
			action = new TokenDelAction(x,y,spriteList);
			break;

		case Move:
			action = new TokenMoveAction(*selectedSprite_,x,y,spriteList);
			break;

		default:
            action = new TokenNoAction(x,y);
			break;
	}
	if(!isMovementAnimation_){
		selectedSprite_ = nullptr;
	}
 return *action;
}

