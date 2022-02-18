#include "AudioBuffer.h"


AudioBuffer::AudioBuffer(int bufferSize)
  : writeIndex(0)
  , readIndex(0)
  , delaySize(0)
  , bufferSize(bufferSize)
{
  audioBuffer = new int16_t[bufferSize](); // parens initialize the buffer to all zeroes
}


AudioBuffer::~AudioBuffer() {
  delete audioBuffer;
}


// aCoefficient goes from 0.f to 1.f. Use a 0.f sampleOut to fade in/out.
int16_t AudioBuffer::crossFade(int16_t sampleA, float aCoefficient, int16_t sampleB) {
  return (int16_t)((sampleA * aCoefficient + sampleB * (1.f - aCoefficient)) + 0.5f); // Add 0.5f to round to the nearest whole number
}


void AudioBuffer::setDelaySize(int numSamples) {
  delaySize = numSamples;
}


// Volumes are between 0.f and 1.f
int16_t AudioBuffer::calculateReadSample(int16_t sampleIn, bool reverse, float dryVolume, float wetVolume) {
  int16_t bufferSample = readNextSample(reverse);
  int16_t returnSample = (int16_t)((sampleIn * dryVolume + bufferSample * wetVolume) + 0.5f); // Add 0.5f to round to the nearest whole number

  return returnSample;
}


// Feedback is between 0.0f and 1.0f
int16_t AudioBuffer::calculateWriteSample(int16_t sampleIn, bool reverse, float feedback) {
  int16_t bufferSample = readNextSample(reverse);
  int16_t returnSample = (int16_t)((sampleIn + feedback * bufferSample) + 0.5f); // Add 0.5f to round to the nearest whole number

  return returnSample;
}
