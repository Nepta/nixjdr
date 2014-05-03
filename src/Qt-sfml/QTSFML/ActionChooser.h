#ifndef __ActionChooser_H__
#define __ActionChooser_H__

#include <vector>
#include "QTSFMLCanvas.h"
#include "Action.h"

class ActionChooser{
private:
	ActionChooser(){};

public:
	static ActionChooser& instance();
	Action* choose(int x, int y);
};

#endif /* __ActionChooser_H__ */

