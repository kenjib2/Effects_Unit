#include "MultiTapDelay.h"


MultiTapDelay::MultiTapDelay() {
    primaryDelayBuffer = new CircularBuffer(MAX_DELAY_BUFFER_SIZE);
    primaryDelayBuffer->numReadIndices = 1;
    tapDelayBuffer = new CircularBuffer(MAX_DELAY_BUFFER_SIZE);
    tapDelayBuffer->numReadIndices = 1;
}


MultiTapDelay::~MultiTapDelay() {
    delete primaryDelayBuffer;
    delete tapDelayBuffer;
}


void MultiTapDelay::setPrimaryDelayLength(int delaySamples) {
    primaryDelayBuffer->setDelaySize(0, delaySamples);
}


void MultiTapDelay::setPrimaryDelayLevel(float level) {
    primaryDelayBuffer->setDelayLevel(0, level);
}


void MultiTapDelay::setTapDelayLength(int indexNumber, int delaySamples) {
    tapDelayBuffer->setDelaySize(indexNumber, delaySamples);
}


void MultiTapDelay::setTapDelayLevel(int indexNumber, float level) {
    tapDelayBuffer->setDelayLevel(indexNumber, level);
}


void MultiTapDelay::setNumTaps(int numTaps) {
    tapDelayBuffer->numReadIndices = numTaps;
}


// Handle primary delay, write to buffer, then read the taps (no write)
int16_t MultiTapDelay::processSample(int16_t inputSample) {
    int16_t readSample = tapDelayBuffer->calculateReadSample(inputSample, paramReverse, paramDry, paramWet);
    int16_t writeSample = primaryDelayBuffer->calculateWriteSample(inputSample, paramReverse, paramFeedback);
    tapDelayBuffer->writeNextSample(writeSample);

    readSample = primaryDelayBuffer->calculateReadSample(readSample, paramReverse, paramDry, paramWet);
    writeSample = primaryDelayBuffer->calculateWriteSample(inputSample, paramReverse, paramFeedback);
    primaryDelayBuffer->writeNextSample(writeSample);

    tapDelayBuffer->next(paramReverse);
    primaryDelayBuffer->next(paramReverse);

    return readSample;
}
