#ifndef __CoutAction_H__
#define __CoutAction_H__

#include "Action.h"

class CoutAction : public Action{
public:
	CoutAction(int x, int y);
	void execute();
};


#endif /* __CoutAction_H__ */

