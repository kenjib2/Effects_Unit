#pragma once
#include "AudioBuffer.h"


class CircularBuffer : public AudioBuffer {

protected:
  int firstLatchCount = 0;
  bool needPostLatchFadeIn = false;
  int postLatchCount = 0;

  void incIndices(int* indices);
  void incReverseIndices(int* indices);
  int16_t crossFadeTwoIndices(int previousIndex, int currentIndex, int indexFadeCount);

public:
  CircularBuffer(int bufferSize);
  int indexFadeCount[MAX_READ_INDICES];

  void next(bool reverse) override;
  int16_t readNextSample(int indexNumber, bool reverse) override;
  void writeNextSample(int16_t sample) override;
};
