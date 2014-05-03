#include "ActionChooser.h"
#include "CoutAction.h"
#include "TokenAddAction.h"
#include "SpriteList.h"
#include <iostream>

ActionChooser& ActionChooser::instance(){
	static ActionChooser *instance = new ActionChooser();
	return *instance;
}

Action* ActionChooser::choose(int x, int y){
	Action *action;
	switch(1){
		case 0:
			action = new CoutAction(x,y);
			break;
		case 1:
			action = new TokenAddAction(x,y,SpriteList::instance());
			break;
		default:
			break;
	}
 return action;
}


