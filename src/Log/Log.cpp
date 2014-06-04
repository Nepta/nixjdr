#include "Log.h"

Log::Log(Receiver& receiver) : receiver_(receiver), message_(QString("")){
}

Receiver& Log::reveiver(){
	return receiver_;
}

QString Log::toString(){
	return getMessage().getString();
}

void Log::setMessage(Message message){
	message_ = message;
}

void Log::setHeader(Header head){
	header_ = head;
}

Message& Log::getMessage(){
	return message_;
}

Header& Log::getHeader(){
	return header_;
}
