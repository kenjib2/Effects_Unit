#include "GrainPool.h"


GrainPool::GrainPool(int maxGrains)
	: maxGrains(maxGrains)
{
	grainPool = new Grain[maxGrains]();
}


GrainPool::~GrainPool() {
	delete grainPool;
}


Grain* GrainPool::getGrain(int16_t* buffer, int size, GrainEnvelope* envelope) {
	for (int i = 0; i < maxGrains; i++) {
		Grain* nextGrain = &grainPool[i];
		if (!nextGrain->active) {
			nextGrain->active = true;
			nextGrain->buffer = buffer;
			nextGrain->size = size;
			nextGrain->envelope = envelope;
			return nextGrain;
		}
	}

	return NULL;
}


void GrainPool::returnGrain(Grain grain) {
	grain.active = false;
}
