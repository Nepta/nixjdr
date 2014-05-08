#ifndef __TokenDelAction_H__
#define __TokenDelAction_H__

#include "GraphicAction.h"

class TokenDelAction : public GraphicAction{

public:
	TokenDelAction(int x, int y, SpriteList& spriteList) : GraphicAction(x,y,spriteList){}
	void execute(){
		spriteList_.delSprite(x(), y());
	}
};

#endif /* __TokenDelAction_H__ */

