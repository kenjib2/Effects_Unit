#pragma once
#include "AudioBuffer.h"


class CircularBuffer : public AudioBuffer {

protected:
  // Used to track the current iteration through a single delay cycle so that the size of the delay will
  // only be updated at the beginning of each cycle instead of constantly.
  int currentLoopSize;
  int firstLatchCount = 0;
  bool needPostLatchFadeIn = false;
  int postLatchCount = 0;

  bool atLoopStart() override;

public:
  CircularBuffer(int bufferSize);

  void next(bool reverse) override;
  int16_t readNextSample(int indexNumber, bool reverse) override;
  void writeNextSample(int16_t sample) override;
};
