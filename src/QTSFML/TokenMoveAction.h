#ifndef __TokenMoveAction_H__
#define __TokenMoveAction_H__

#include "GraphicAction.h"

class TokenMoveAction : public GraphicAction{
	sf::Sprite& spriteToMove_;
public:
	TokenMoveAction(sf::Sprite& spriteToMove, int x, int y) :
		GraphicAction(x,y), spriteToMove_(spriteToMove){}
	
	void execute(){
		spriteToMove_.setPosition(x(),y());
	}
};

#endif /* __TokenMoveAction_H__ */
