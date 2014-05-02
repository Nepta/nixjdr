#include "ActionChooser.h"
#include "CoutAction.h"
#include "TokenAddAction.h"
#include <iostream>

ActionChooser& ActionChooser::instance(){
	static ActionChooser *instance = new ActionChooser();
	return *instance;
}

void ActionChooser::spriteList(SpriteList& spriteList){
	spriteList_ = &spriteList;
}

SpriteList& ActionChooser::spriteList(){
	return *spriteList_;
}

Action* ActionChooser::choose(int x, int y){
	Action *action;
	switch(1){
		case 0:
			action = new CoutAction(x,y);
			break;
		case 1:
			action = new TokenAddAction(x,y,*spriteList_);
			break;
		default:
			break;
	}
 return action;
}


