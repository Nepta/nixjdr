#include <iostream>
#include "CoutAction.h"

CoutAction::CoutAction(int x, int y) : Action(x,y){}

void CoutAction::execute(){
	std::cout << "(" << x() << "," << y() << ")" << std::endl;
}
