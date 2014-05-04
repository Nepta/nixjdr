#include "ActionChooser.h"
#include "CoutAction.h"
#include "TokenAddAction.h"
#include "TokenDelAction.h"
#include "TokenMoveAction.h"
#include "SpriteList.h"
#include <QDebug>

ActionChooser& ActionChooser::instance(){
	static ActionChooser *instance = new ActionChooser();
	return *instance;
}

void ActionChooser::selectSprite(int x, int y){
	selectedSprite_ = SpriteList::instance().searchSprite(x,y);
}

void ActionChooser::isMoving(bool state){
	isMovementAnimation_ = state;
}

ActionChooser::ActionType ActionChooser::selectAction(int x, int y){
	void* hasSprite = SpriteList::instance().searchSprite(x,y);
	ActionType type = Cout;
	if(selectedSprite_ != nullptr){
		if(isMovementAnimation_ || hasSprite == nullptr){
			type = Move;
		}
	}else if(!isMovementAnimation_){
		switch((hasSprite != 0) + 1){
			case 0:
				type = Cout;
				break;
	
			case 1:
				type = Add;
				break;
	
			case 2:
				type = Remove;
				break;
	
			default:
				type = Cout;
				break;
		}
	}
	return type;
}

Action& ActionChooser::choose(int x, int y){
	Action *action;
	ActionType type(selectAction(x,y));
	switch(type){
		case Cout:
			action = new CoutAction(x,y);
			break;

		case Add:
			action = new TokenAddAction(x,y);
			break;

		case Remove:
			action = new TokenDelAction(x,y);
			break;

		case Move:
			action = new TokenMoveAction(*selectedSprite_,x,y);
			break;

		default:
			action = new CoutAction(x,y);
			break;
	}
	if(!isMovementAnimation_){
		selectedSprite_ = nullptr;
	}
 return *action;
}

