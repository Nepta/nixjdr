#ifndef __CoutAction_H__
#define __CoutAction_H__

#include "Action.h"

class NoAction : public Action{
public:
    NoAction(int x, int y);
	void execute();
};


#endif /* __CoutAction_H__ */

