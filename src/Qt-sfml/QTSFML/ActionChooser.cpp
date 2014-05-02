#include "ActionChooser.h"
#include "CoutAction.h"

ActionChooser& ActionChooser::instance(){
	static ActionChooser *instance = new ActionChooser();
	return *instance;
}

Action* ActionChooser::choose(int x, int y){
	Action *action;
	switch([]()->int{return 0;}()){
		case 0:
			action = new CoutAction(x,y);
		default:
			break;
	}
 return action;
}
