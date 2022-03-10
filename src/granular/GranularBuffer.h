#include "Arduino.h"
#include "GrainPool.h"


// Grains typically range from 1ms (44.1 samples) to 100ms (4410 samples)
const int MAX_GRAIN_SIZE = 1000;
const int MAX_NUM_GRAINS = 20;
const int GRANULAR_CROSSFADE_LENGTH = 50;


class GranularBuffer {
public:
	int16_t** grainBuffer;
	int numGrains;
	int maxGrainSize;
	int grainSize;
	int maxGrainCrossfadeLength;
	int grainCrossfadeLength;
	float speedMultiplier;  // 1.f is no pitch shift, 0.5f is one octave lower (half speed), 2.f is one octave higher (double speed), etc.

	GranularBuffer(GrainPool* grainPool, int numGrains = MAX_NUM_GRAINS, int maxGrainSize = MAX_GRAIN_SIZE, int grainCrossfadeLength = GRANULAR_CROSSFADE_LENGTH);
	~GranularBuffer();

	void loadSamples(int16_t* buffer, int size);
	Grain* getPreviousGrain(int count, GrainEnvelope* envelope);  // Get the grain that was stored *count* grains ago. Must be 1 or higher. Returns null if no grain is available from the pool.
	int16_t getNextSample();

protected:
	GrainPool* grainPool;
	int writeGrain;
	int writeIndex;
	int readGrain;
	float readIndex;
};
