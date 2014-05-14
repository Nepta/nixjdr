#ifndef DECODER_H
#define DECODER_H

#include <QObject>

class Decoder{
public:
	Decoder();

	template<class T>
	static T decode(QObject encodedObject){
		return dynamic_cast<T>(encodedObject);
	}
};

#endif // DECODER_H
