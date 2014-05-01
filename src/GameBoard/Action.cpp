#include "Action.h"

Action::Action(int x, int y) : x_(x), y_(y){}

int Action::x(){
	return x_;
}

int Action::y(){
	return y_;
}
