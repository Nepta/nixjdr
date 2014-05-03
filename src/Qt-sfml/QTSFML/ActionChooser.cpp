#include "ActionChooser.h"
#include "CoutAction.h"
#include "TokenAddAction.h"
#include "TokenDelAction.h"
#include "SpriteList.h"
#include <iostream>

ActionChooser& ActionChooser::instance(){
	static ActionChooser *instance = new ActionChooser();
	return *instance;
}

ActionChooser::ActionType ActionChooser::selectAction(int x, int y){
	void* hasSprite = SpriteList::instance().searchSprite(x,y);
	ActionType type;
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
	return type;
}

Action* ActionChooser::choose(int x, int y){
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
		default:
			break;
	}
 return action;
}


