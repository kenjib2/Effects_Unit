#ifndef GRAIN_H
#define GRAIN_H


#include "Arduino.h"
#include "GrainEnvelope.h"


class Grain {
public:
	bool active = false;
	int16_t* buffer;
	int size;
	GrainEnvelope* envelope;
};


#endif // #ifndef GRAIN_H
