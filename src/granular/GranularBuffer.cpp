#include "GranularBuffer.h"


GranularBuffer::GranularBuffer(GrainPool* grainPool, int numGrains, int maxGrainSize, int maxGrainCrossfadeLength)
	: numGrains(numGrains)
	, maxGrainSize(maxGrainSize)
	, grainSize(maxGrainSize)
	, maxGrainCrossfadeLength(maxGrainCrossfadeLength)
	, grainCrossfadeLength(maxGrainCrossfadeLength)
	, speedMultiplier(1.f)
	, grainPool(grainPool)
	, writeGrain(0)
	, writeIndex(0)
	, readGrain(numGrains - 1)
	, readIndex(0.f)
{
	grainBuffer = new int16_t * [numGrains];
	for (int i = 0; i < numGrains; i++) {
		grainBuffer[i] = new int16_t[maxGrainSize]();
	}
}


GranularBuffer::~GranularBuffer() {
	for (int i = 0; i < numGrains; i++) {
		delete grainBuffer[i];
	}
	delete grainBuffer;
}


void GranularBuffer::loadSamples(int16_t* buffer, int size) {
	for (int i = 0; i < size; i++) {
		grainBuffer[writeGrain][writeIndex] = buffer[i];
		writeIndex++;
		if (writeIndex >= grainSize) {
			if (maxGrainSize > grainSize) {
				// Clear the rest of the grain data if the grain size is smaller than the max
				// This prevents old data still being there later if grain sizes change.
				memset(grainBuffer[writeGrain], 0, (maxGrainSize - grainSize) * sizeof(int16_t));
			}
			writeIndex = 0;
			writeGrain++;
			if (writeGrain >= numGrains) {
				writeGrain = 0;
			}
		}
	}
}


Grain* GranularBuffer::getPreviousGrain(int count, GrainEnvelope* envelope) {
	int readGrain = writeGrain - count;
	if (readGrain < 0) {
		readGrain += numGrains;
	}

	return grainPool->getGrain(grainBuffer[readGrain], grainSize, envelope);
}


int16_t GranularBuffer::getNextSample() {
	int curIndex = (int)floor(readIndex);
	int nextIndex = curIndex + 1;
	if (nextIndex >= grainSize) {
		nextIndex -= grainSize;
	}

	double fractionalIndex = readIndex - (double)curIndex;

	int16_t curSample = grainBuffer[readGrain][curIndex];
	int16_t nextSample = grainBuffer[readGrain][nextIndex];

	int16_t readSample = (int16_t)((1 - fractionalIndex) * curSample + fractionalIndex * nextSample);


	if (writeIndex - curIndex <= GRANULAR_CROSSFADE_LENGTH) {

	}


	readIndex += speedMultiplier;
	if ((int)floor(readIndex) >= grainSize) {
		readIndex -= grainSize;
		readGrain++;
		if (readGrain >= numGrains) {
			readGrain = 0;
		}
	}

	return readSample;
}
