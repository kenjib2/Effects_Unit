#include "Util.h"


float scaleLinToExp(int input, int rangeMin, int rangeMax) {
  float retVal = (float)(input - rangeMin) / (rangeMax - rangeMin);
  retVal = powf(retVal, 2);
  retVal = retVal * (rangeMax - rangeMin) + rangeMin;
  return retVal;
}


int16_t linearInterpolation(int16_t* buffer, int bufferSize, float floatIndex) {
	int curIndex = (int)floor(floatIndex);
	int nextIndex = curIndex + 1;
	if (nextIndex >= bufferSize) {
		nextIndex -= bufferSize;
	}
	double fractionalIndex = floatIndex - (double)curIndex;

	int16_t curSample = buffer[curIndex];
	int16_t nextSample = buffer[nextIndex];

	return (int16_t)((1 - fractionalIndex) * curSample + fractionalIndex * nextSample);
}
