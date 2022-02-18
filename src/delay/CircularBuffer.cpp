#include "CircularBuffer.h"


CircularBuffer::CircularBuffer(int bufferSize)
  : AudioBuffer(bufferSize) {
  return;
}


int CircularBuffer::getReverseIndex() {
  return 0;
}


// Need to fix this
bool CircularBuffer::atLoopStart() {
  if (readIndex == 0) {
    return true;
  }
  return false;
}


void CircularBuffer::next() {
  readIndex++;
  if (readIndex >= bufferSize) {
    readIndex -= bufferSize;
  }
  writeIndex++;
  if (writeIndex >= bufferSize) {
    writeIndex -= bufferSize;
  }
}


int16_t CircularBuffer::readNextSample(bool reverse) {
  // Should the loop start check be for read or write?
  if (atLoopStart()) {
    currentLoopSize = delaySize;
    readIndex = writeIndex - delaySize;
    while (readIndex < 0) {
      readIndex += bufferSize;
    }
  }
  return audioBuffer[readIndex];
}


void CircularBuffer::writeNextSample(int16_t sample) {
    audioBuffer[writeIndex] = sample;
}
