#ifndef __GraphicAction_H__
#define __GraphicAction_H__

#include <vector>
#include "Action.h"

typedef std::vector<std::pair<sf::Texture, std::vector<sf::Sprite>>> SpriteList;
class GraphicAction : public Action{

protected:
	SpriteList& spriteList_;

public:
	GraphicAction(int x, int y, SpriteList& spriteList) : Action(x,y), spriteList_(spriteList){}
	virtual void execute() = 0;
};

#endif /* __GraphicAction_H__ */

