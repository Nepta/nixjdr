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

Action* ActionChooser::choose(int x, int y){
	Action *action;
	void* hasSprite = SpriteList::instance().searchSprite(x,y);
	switch((hasSprite != 0) + 1){
		case 0:
			action = new CoutAction(x,y);
			break;
		case 1:
			action = new TokenAddAction(x,y);
			break;
		case 2:
			action = new TokenDelAction(x,y);
			break;
		default:
			break;
	}
 return action;
}


