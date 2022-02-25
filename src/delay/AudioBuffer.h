#pragma once
#include "Arduino.h"
#include "../../Util.h"


const float MIN_DELAY_TIME_PARAM = 0.020f;
const float MAX_DELAY_BUFFER_SECONDS = 1.0;
const int DELAY_SAMPLE_RATE = 44100;
const int MAX_DELAY_BUFFER_SIZE = (int)(DELAY_SAMPLE_RATE * MAX_DELAY_BUFFER_SECONDS);
const int MAX_READ_INDICES = 16;


class AudioBuffer {

protected:
  int16_t* audioBuffer;
  int writeIndex;
  int readIndices[MAX_READ_INDICES];
  int delaySize[MAX_READ_INDICES];
  float delayLevels[MAX_READ_INDICES];

//  int16_t crossFade(int16_t sampleA, float aCoefficient, int16_t sampleB);
  virtual int getReverseIndex(int indexNumber) = 0;
  virtual bool atLoopStart() = 0;

public:
  int bufferSize;
  int numReadIndices;

  AudioBuffer(int bufferSize);
  virtual ~AudioBuffer();

  void setDelaySize(int indexNumber, int numSamples);
  void setDelayLevel(int indexNumber, float level); // Level between 0.0f and 1.0f
  virtual void next() = 0;
  virtual int16_t readNextSample(int indexNumber, bool reverse) = 0;
  virtual void writeNextSample(int16_t sample) = 0;
  // Volumes and feedback are between 0.f and 1.f
  int16_t calculateReadSample(int16_t sampleIn, bool reverse, float dryVolume, float wetVolume);
  int16_t calculateWriteSample(int16_t sampleIn, bool reverse, float feedback);  

};