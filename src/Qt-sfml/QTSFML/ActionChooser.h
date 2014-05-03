#ifndef __ActionChooser_H__
#define __ActionChooser_H__

#include <vector>
#include "QTSFMLCanvas.h"
#include "Action.h"

class ActionChooser{
private:
	ActionChooser(){};
	enum ActionType{
		Cout,
		Remove,
		Add,
		Move
	};
	
public:
	static ActionChooser& instance();
	Action* choose(int x, int y);
	ActionType selectAction(int x, int y);
};

#endif /* __ActionChooser_H__ */

