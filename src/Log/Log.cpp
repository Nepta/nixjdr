#include "Log.h"

Log::Log(Receiver& receiver) : receiver_(receiver){
}


Receiver& Log::reveiver(){
	return receiver_;
}
