#ifndef GRAIN_POOL_H
#define GRAIN_POOL_H


#include "Grain.h"


class GrainPool {
public:
	GrainPool(int maxGrains);
	~GrainPool();

	Grain* getGrain(int16_t * buffer, int size, GrainEnvelope* envelope);  // Returns 0 if no grain is available from the pool.
	void returnGrain(Grain grain);

protected:
	int maxGrains;
	Grain * grainPool;
};


#endif // #ifndef GRAIN_POOL_H