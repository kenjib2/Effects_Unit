#include "CircularBuffer.h"


CircularBuffer::CircularBuffer(int bufferSize)
  : AudioBuffer(bufferSize) {
  return;
}


// Need to fix this
bool CircularBuffer::atLoopStart() {
  if (readIndices[0] == 0) {
    return true;
  }
  return false;
}


void CircularBuffer::next(bool reverse) {
  for (int i = 0; i < numReadIndices; i++) {
    if (reverse) {
      readIndices[i]--;
      if (readIndices[i] < 0) {
          readIndices[i] += bufferSize;
      }
      int relativeIndex = readIndices[i];
      if (relativeIndex > writeIndex) {
          relativeIndex -= bufferSize;
      }
      if (writeIndex - relativeIndex >= min(bufferSize - 1, delaySize[i] * 2)) {
          readIndices[i] = writeIndex;
      }
    }
    else {
      readIndices[i]++;
      if (readIndices[i] >= bufferSize) {
        readIndices[i] -= bufferSize;
      }
    }
  }
  writeIndex++;
  if (writeIndex >= bufferSize) {
    writeIndex -= bufferSize;
  }
}


int16_t CircularBuffer::readNextSample(int indexNumber, bool reverse) {
  // Should the loop start check be for read or write or next?
/*  if (atLoopStart()) {
    currentLoopSize = delaySize[indexNumber];
    readIndices[indexNumber] = writeIndex - delaySize[indexNumber];
    while (readIndices[indexNumber] < 0) {
      readIndices[indexNumber] += bufferSize;
    }
  }*/
  int16_t nextSample = audioBuffer[readIndices[indexNumber]];
  if (reverse) {
      int relativeIndex = readIndices[indexNumber];
      if (relativeIndex > writeIndex) {
          relativeIndex -= bufferSize;
      }
      int remaining = min(bufferSize - 1, delaySize[indexNumber] * 2) - (writeIndex - relativeIndex);
      if (remaining < FADE_SAMPLES) {
          //fade out the end of a reverse delay loop
          nextSample = crossFade(nextSample, (float)remaining / FADE_SAMPLES, 0.f);
      }
      else if (writeIndex - relativeIndex < FADE_SAMPLES) {
          //fade in the beginning of a reverse delay loop
          nextSample = crossFade(nextSample, (float)(writeIndex - relativeIndex) / FADE_SAMPLES, 0.f);
      }
  }
  // Fade out the tail of the first latch so we don't get a pop
  if (isFirstLatch) {
    if (latchSize - firstLatchCount < FADE_SAMPLES) {
        nextSample = crossFade(nextSample, (float)(latchSize - firstLatchCount) / FADE_SAMPLES, 0.f);
//        nextSample = (float)(latchSize - firstLatchCount) / FADE_SAMPLES * nextSample;
    }
  }
  return nextSample;
}


void CircularBuffer::writeNextSample(int16_t sample) {
    int16_t writeSample = sample;
    if (isLatched && isFirstLatch) {
        if (firstLatchCount < FADE_SAMPLES) {
            writeSample = crossFade(writeSample, (float)firstLatchCount / FADE_SAMPLES, 0.f);
//            writeSample = (float)firstLatchCount / FADE_SAMPLES * writeSample;
        }
        else if (latchSize - firstLatchCount < FADE_SAMPLES) {
            writeSample = crossFade(writeSample, (float)(latchSize - firstLatchCount) / FADE_SAMPLES, 0.f);
//            writeSample = (float)(latchSize - firstLatchCount) / FADE_SAMPLES * writeSample;
        }
        audioBuffer[writeIndex] = writeSample;
        firstLatchCount++;
        if (firstLatchCount > latchSize) {
            Serial.println("First latch done");
            isFirstLatch = false;
            needPostLatchFadeIn = true;
            firstLatchCount = 0;
        }
    } else if (isLatched) {
        int latchIndex = writeIndex - latchSize;
        if (latchIndex < 0) {
            latchIndex += bufferSize;
        }
        audioBuffer[writeIndex] = audioBuffer[latchIndex];
    }
    else {
        if (needPostLatchFadeIn) {
            writeSample = crossFade(writeSample, (float)postLatchCount / FADE_SAMPLES, 0.f);
            postLatchCount++;
            if (postLatchCount >= FADE_SAMPLES) {
                postLatchCount = 0;
                needPostLatchFadeIn = false;
            }
        }
        audioBuffer[writeIndex] = writeSample;
    }
}
