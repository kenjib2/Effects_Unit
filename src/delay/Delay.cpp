#include "Delay.h"


Delay::Delay() {
  delayBuffer = new CircularBuffer(MAX_DELAY_BUFFER_SIZE);
  delayBuffer->numReadIndices = 1;
  delayBuffer->setDelayLevel(0, 1.0f);
}


Delay::~Delay() {
  delete delayBuffer;
}


void Delay::setDelayLength(int delaySamples) {
  delayBuffer->setDelaySize(0, delaySamples);
}


    
int16_t Delay::processSample(int16_t inputSample) {
  int16_t readSample = delayBuffer->calculateReadSample(inputSample, paramReverse, paramDry, paramWet);
  int16_t writeSample = delayBuffer->calculateWriteSample(inputSample, paramReverse, paramFeedback);
  delayBuffer->writeNextSample(writeSample);
  delayBuffer->next();

  return readSample;
}
