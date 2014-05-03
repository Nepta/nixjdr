#ifndef __TokenAddAction_H__
#define __TokenAddAction_H__

#include "GraphicAction.h"

class TokenAddAction : public GraphicAction{

public:
	TokenAddAction(int x, int y) : GraphicAction(x,y){}
	void execute(){
		spriteList_.addSprite(x(), y());
	}
};

#endif /* __TokenAddAction_H__ */

