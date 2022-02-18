#include "Arduino.h"


class AudioBuffer {

protected:
  int16_t* audioBuffer;
  int writeIndex;
  int readIndex;
  int delaySize;

  int16_t crossFade(int16_t sampleA, float aCoefficient, int16_t sampleB);
  virtual int getReverseIndex() = 0;
  virtual bool atLoopStart() = 0;

public:
  int bufferSize;

  AudioBuffer(int bufferSize);
  virtual ~AudioBuffer();

  void setDelaySize(int numSamples);
  virtual void next() = 0;
  virtual int16_t readNextSample(bool reverse) = 0;
  virtual void writeNextSample(int16_t sample) = 0;
  // Volumes and feedback are between 0.f and 1.f
  int16_t calculateReadSample(int16_t sampleIn, bool reverse, float dryVolume, float wetVolume);
  int16_t calculateWriteSample(int16_t sampleIn, bool reverse, float feedback);  

};
