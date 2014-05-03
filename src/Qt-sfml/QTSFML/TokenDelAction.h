#ifndef __TokenDelAction_H__
#define __TokenDelAction_H__

#include "GraphicAction.h"

class TokenDelAction : public GraphicAction{

public:
	TokenDelAction(int x, int y) : GraphicAction(x,y){}
	void execute(){
		spriteList_.delSprite(x(), y());
	}
};

#endif /* __TokenDelAction_H__ */

