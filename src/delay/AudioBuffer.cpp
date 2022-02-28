#include "AudioBuffer.h"


AudioBuffer::AudioBuffer(int bufferSize)
  : writeIndex(0)
  , bufferSize(bufferSize)
  , numReadIndices(1)
{
  for (int i = 0; i < MAX_READ_INDICES; i++) {
    readIndices[i] = 0;
    delaySize[i] = MIN_DELAY_TIME_PARAM;
    delayLevels[i] = 0.0f;
  }
  audioBuffer = new int16_t[bufferSize](); // parens initialize the buffer to all zeroes
}


AudioBuffer::~AudioBuffer() {
  delete audioBuffer;
}


// aCoefficient goes from 0.f to 1.f. Use a 0.f sampleB to fade in/out.
int16_t AudioBuffer::crossFade(int16_t sampleA, float aCoefficient, int16_t sampleB) {
  return (int16_t)((sampleA * aCoefficient + sampleB * (1.f - aCoefficient)) + 0.5f); // Add 0.5f to round to the nearest whole number
}


void AudioBuffer::setDelaySize(int indexNumber, int numSamples) {
  delaySize[indexNumber] = numSamples;
  readIndices[indexNumber] = writeIndex - numSamples;
  while (readIndices[indexNumber] < 0) {
      readIndices[indexNumber] += bufferSize;
  }
}


int AudioBuffer::getDelaySize(int indexNumber) {
    return delaySize[indexNumber];
}


void AudioBuffer::setDelayLevel(int indexNumber, float level) {
    delayLevels[indexNumber] = level;
}


int AudioBuffer::getReadIndex(int indexNumber) {
    return readIndices[indexNumber];
}


void AudioBuffer::setWriteInsert(WriteInsert* writeInsertObject) {
    writeInsert = writeInsertObject;
}


void AudioBuffer::startLatch(int indexNumber) {
    isLatched = true;
    isFirstLatch = true;
    latchSize = delaySize[indexNumber];
}


void AudioBuffer::stopLatch() {
    isLatched = false;
}


// Volumes are between 0.f and 1.f
int16_t AudioBuffer::calculateReadSample(int16_t sampleIn, bool reverse, float dryVolume, float wetVolume) {
  int16_t bufferSample = 0;
  for (int i = 0; i < numReadIndices; i++) {
      bufferSample += readNextSample(i, reverse) * delayLevels[i];
  }
  int16_t returnSample = (int16_t)((sampleIn * dryVolume + bufferSample * wetVolume) + 0.5f); // Add 0.5f to round to the nearest whole number

  return returnSample;
}


// Feedback is between 0.0f and 1.0f
int16_t AudioBuffer::calculateWriteSample(int16_t sampleIn, bool reverse, float feedback) {
  int16_t bufferSample = 0;
  for (int i = 0; i < numReadIndices; i++) {
      bufferSample += readNextSample(i, reverse);
  }
  int16_t returnSample = sampleIn;
  if (feedback > EPSILON) {
      returnSample = (int16_t)((sampleIn + feedback * bufferSample) + 0.5f); // Add 0.5f to round to the nearest whole number
  }

  if (writeInsert != 0) {
      returnSample = writeInsert->processSample(returnSample);
  }

  return returnSample;
}
