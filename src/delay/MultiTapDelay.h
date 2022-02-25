#pragma once
#include "CircularBuffer.h"


class MultiTapDelay {
  public:
    bool paramReverse = false;
    float paramDry = 0.8;
    float paramWet = 0.5;
    float paramFeedback = 0.0;

    MultiTapDelay();
    ~MultiTapDelay();

    int16_t processSample(int16_t inputSample);
    void setPrimaryDelayLength(int delaySamples);
    void setPrimaryDelayLevel(float level);
    void setTapDelayLength(int indexNumber, int delaySamples);
    void setTapDelayLevel(int indexNumber, float level);
    void setNumTaps(int numTaps);

  protected:
    AudioBuffer* primaryDelayBuffer;
    AudioBuffer* tapDelayBuffer;
};
