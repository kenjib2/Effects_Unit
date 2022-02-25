#include "CircularBuffer.h"


CircularBuffer::CircularBuffer(int bufferSize)
  : AudioBuffer(bufferSize) {
  return;
}


int CircularBuffer::getReverseIndex(int indexNumber) {
  return 0;
}


// Need to fix this
bool CircularBuffer::atLoopStart() {
  if (readIndices[0] == 0) {
    return true;
  }
  return false;
}


void CircularBuffer::next() {
  for (int i = 0; i < numReadIndices; i++) {
    readIndices[i]++;
    if (readIndices[i] >= bufferSize) {
      readIndices[i] -= bufferSize;
    }
  }
  writeIndex++;
  if (writeIndex >= bufferSize) {
    writeIndex -= bufferSize;
  }
}


int16_t CircularBuffer::readNextSample(int indexNumber, bool reverse) {
  // Should the loop start check be for read or write?
/*  if (atLoopStart()) {
    currentLoopSize = delaySize[indexNumber];
    readIndices[indexNumber] = writeIndex - delaySize[indexNumber];
    while (readIndices[indexNumber] < 0) {
      readIndices[indexNumber] += bufferSize;
    }
  }*/
  return audioBuffer[readIndices[indexNumber]];
}


void CircularBuffer::writeNextSample(int16_t sample) {
    audioBuffer[writeIndex] = sample;
}
