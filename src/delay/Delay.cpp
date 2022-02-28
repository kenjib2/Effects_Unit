#include "Delay.h"


Delay::Delay() {
  delayBuffer = new CircularBuffer(MAX_DELAY_BUFFER_SIZE);
  delayBuffer->numReadIndices = 1;
  delayBuffer->setDelayLevel(0, 1.0f);
  sensitivityTriggered = false;
}


Delay::~Delay() {
  delete delayBuffer;
}


void Delay::setDelayLength(int delaySamples) {
  delaySize = delaySamples;
  delayBuffer->setDelaySize(0, delaySamples);
}


void Delay::setLoopLatch(float loopLatch) {
    paramLoopLatch = loopLatch;
    paramLoopLatchLog = paramLoopLatch * paramLoopLatch * paramLoopLatch; // We want a logorithmic response rate
}


void Delay::setWriteInsert(WriteInsert* writeInsertObject) {
    delayBuffer->setWriteInsert(writeInsertObject);
}


int16_t Delay::processSample(int16_t inputSample) {
  if (loopPosition == 0) {
    Serial.println("Loop start");
    // Managing latches this cycle -- don't latch if we aren't triggered
    if (!isLatched && sensitivityTriggered) {
        float rand = (float)random(1000) / 1000 ;
        if (rand > (1.f - paramLoopLatchLog)) {
            isLatched = true;
            timeLatchCount = 15 - 8 * rand;
            delayBuffer->startLatch(0);
            Serial.println("Latch on");
        }
    }
    if (isLatched && timeLatchCount <= 0) {
        isLatched = false;
        delayBuffer->stopLatch();
        Serial.println("Latch off");
    }
    if (timeLatchCount > 0) {
        timeLatchCount--;
    }
  }

  if (abs(inputSample) > 32767 - paramSensitivity) {
    peakReleaseCount = 0;
    sensitivityTriggered = true;  // Sensitivity will turn off latch when the threshold is exceeded
  } 
  else if (sensitivityTriggered) {
	  peakReleaseCount++;
      if (peakReleaseCount > delaySize) {
          sensitivityTriggered = false;
      }
  }
	
  int16_t readSample = delayBuffer->calculateReadSample(inputSample, paramReverse, paramDry, paramWet);
  int16_t writeSample = 0;
  int16_t calculatedInputSample = inputSample;
  if (sensitivityTriggered) {
    // Fade in when sensitivity is triggered
    if (fadePosition > 0) {
      calculatedInputSample = (int16_t)((float)calculatedInputSample * (FADE_SAMPLES - fadePosition) / FADE_SAMPLES);
      fadePosition--;
    }
  }
  else {
    // Fade out when sensitivity ends
    if (fadePosition < FADE_SAMPLES) {
      calculatedInputSample = (int16_t)((float)calculatedInputSample * (FADE_SAMPLES - fadePosition) / FADE_SAMPLES);
      fadePosition++;
    }
    else {
      calculatedInputSample = 0;
    }
  }
  writeSample = delayBuffer->calculateWriteSample(calculatedInputSample, paramReverse, paramFeedback);
  delayBuffer->writeNextSample(writeSample);
  delayBuffer->next(paramReverse);
  loopPosition++;
  if (loopPosition >= delayBuffer->getDelaySize(0)) {
      loopPosition = 0;
  }

  return readSample;
}
