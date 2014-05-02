#ifndef __TokenAddAction_H__
#define __TokenAddAction_H__

#include "GraphicAction.h"

class TokenAddAction : public GraphicAction{

public:
	TokenAddAction(int x, int y, SpriteList& spriteList) : GraphicAction(x,y,spriteList){}
	void execute(){
		sf::Sprite *firstSpriteCopy = new sf::Sprite(spriteList_[0].first);
		firstSpriteCopy->setPosition(x(),y());
		spriteList_[0].second.push_back(*firstSpriteCopy);
	}
};

#endif /* __TokenAddAction_H__ */

