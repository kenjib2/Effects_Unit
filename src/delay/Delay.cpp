#include "Delay.h"


Delay::Delay() {
  delayBuffer = new CircularBuffer(MAX_DELAY_BUFFER_SIZE);
}


Delay::~Delay() {
  delete delayBuffer;
}


void Delay::setDelayLength(int delaySamples) {
  delayBuffer->setDelaySize(delaySamples);
}


    
int16_t Delay::processSample(int16_t inputSample) {
  int16_t readSample = delayBuffer->calculateReadSample(inputSample, paramReverse, paramDry, paramWet);
  int16_t writeSample = delayBuffer->calculateWriteSample(inputSample, paramReverse, paramFeedback);
  delayBuffer->writeNextSample(writeSample);
  delayBuffer->next();

  return readSample;
}
