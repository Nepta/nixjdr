#ifndef __GraphicAction_H__
#define __GraphicAction_H__

#include "Action.h"
typedef SpriteList std::vector<std::pair<sf::Texture, std::vector<sf::Sprite>>>;
class GraphicAction : public Action{
	SpriteList& spriteList_;

public:
	GraphicAction(int x, int y, SpriteList& spriteList) : Action(x,y), spriteList_(spriteList){}
	virtual void execute() = 0;
};

#endif /* __GraphicAction_H__ */

