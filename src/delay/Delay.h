#include "CircularBuffer.h"


const float MIN_DELAY_TIME_PARAM = 0.020f;
const int MAX_DELAY_BUFFER_SECONDS = 1;
const int DELAY_SAMPLE_RATE = 44100;
const int MAX_DELAY_BUFFER_SIZE = DELAY_SAMPLE_RATE * MAX_DELAY_BUFFER_SECONDS;


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
    int timeOffset = 0;
};
