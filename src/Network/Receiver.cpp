#include "Receiver.h"

Receiver::~Receiver(){}


bool Receiver::isLoggable(){
	return isLoggable_;
}

void Receiver::isLoggable(bool newStatus){
	isLoggable_	= newStatus;
}
