#ifndef __TokenNoAction_H__
#define __TokenNoAction_H__

#include "Action.h"

class TokenNoAction : public Action{
public:
    TokenNoAction(int x, int y);
	void execute();
};


#endif /* __TokenNoAction_H__ */

