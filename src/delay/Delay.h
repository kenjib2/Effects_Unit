#pragma once
#include "CircularBuffer.h"


class Delay {
  public:
    bool paramReverse = false;
    float paramDry = 0.8;
    float paramWet = 0.2;
    float paramFeedback = 0.2;
  
    Delay();
    ~Delay();
    
    int16_t processSample(int16_t inputSample);
    void setDelayLength(int delaySamples);

  protected:
    AudioBuffer * delayBuffer;
};
