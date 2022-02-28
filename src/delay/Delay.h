#pragma once
#include "CircularBuffer.h"


class Delay {
  public:
    bool paramReverse = false;
    float paramDry = 0.8; // Between 0.0 and 1.0
    float paramWet = 0.2; // Between 0.0 and 1.0
    float paramFeedback = 0.2; // Between 0.0 and 1.0
    int paramSensitivity = 32767; // Threshold for delay buffer writes in samples between 0 (always off) and 32767 (always on)

    Delay();
    ~Delay();
    
    int16_t processSample(int16_t inputSample);
    void setDelayLength(int delaySamples);
    void setLoopLatch(float loopLatch); // Between 0.0 and 1.0
    void setWriteInsert(WriteInsert* writeInsertObject);

  protected:
    float paramLoopLatch = 0.0; // Between 0.0 and 1.0
    float paramLoopLatchLog = paramLoopLatch * paramLoopLatch; // We want a logorithmic response rate
    AudioBuffer * delayBuffer;
    int delaySize = 0;
    int loopPosition = 0;
    int fadePosition = 0;
    bool sensitivityTriggered;
    int peakReleaseCount = 0;
    bool isLatched = false;
    int timeLatchCount = 0;
};
