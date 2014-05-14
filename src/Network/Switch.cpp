#include "Switch.h"

Switch::Switch(){
}

Switch &Switch::addNode(Receiver& receiver){
	nodes.append(receiver);
	return *this;
}


