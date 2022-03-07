#pragma once
#include "../chorus/Lfo.h"
#include "../delay/AudioBuffer.h"


// We are starting here already at a 600 sample delay. Adding 1450 takes us to 2050, which is 50ms. +300 samples is @20.4 ms. 20-50 is a typical chorus range.
// Adding 300 or higher sample delay to the main delay line or whatever based on a param to get into chorus sound range. No extra delay is a longish delay flanger
// Typical Flanger delay sizes are @ 221 - 1323 (5ms - 30ms) or @221 or 44 - 309 (1ms - 7ms)
// Typical Chorus delay sizes are 662 - 1544 (15ms - 35ms) or 441 - 2205 (10ms - 50ms) or 265 - 441 (6ms - 10ms)
const int MIN_MODULATION_DELAY = 0;
const int MAX_MODULATION_DELAY = 1200;
const int MODULATION_BUFFER_SIZE = MAX_MODULATION_DELAY + 1;


class Modulation : public WriteInsert {
protected:
    Lfo lfo;
    float floatIndex = MODULATION_BUFFER_SIZE / 2;
    int writeIndex = 0;
    int* modulationBuffer;
    int bufferSize;
    float rate = 1.f; // in Hz
    int modulationWaveform = 0;

public:
    float depth = 0.5f; // delay range from 0.f to 1.fs 
    float doppler = 0.f; // -1.f to 1.f
    float depthScale = 50.f;


    Modulation(int bufSize = MODULATION_BUFFER_SIZE) :
        lfo(44100.f)
    {
        bufferSize = bufSize;
        floatIndex = bufSize / 2;
        modulationBuffer = new int[bufSize]();
        lfo.setWaveform(0);
        lfo.setRate(rate);
        memset(modulationBuffer, 0, bufSize * sizeof(int));
    }


    ~Modulation() {
        delete modulationBuffer;
    }


    void setRate(float newRate) {
        rate = newRate;
        lfo.setRate(newRate);
    }


    void setWaveform(int waveform) {
        modulationWaveform = waveform;
        lfo.setWaveform(waveform);
    }


    int16_t processSample(int16_t sample) override {
        modulationBuffer[writeIndex] = sample;

        int curIndex = (int)floor(floatIndex);
        int nextIndex = curIndex + 1;
        if (nextIndex >= bufferSize) {
            nextIndex -= bufferSize;
        }
        double fractionalIndex = floatIndex - (double)curIndex;

        int16_t curSample = modulationBuffer[curIndex];
        int16_t nextSample = modulationBuffer[nextIndex];

        int16_t readSample = (int16_t)((1 - fractionalIndex) * curSample + fractionalIndex * nextSample);

        writeIndex++;
        if (writeIndex >= bufferSize) {
            writeIndex -= bufferSize;
        }

        // Typical chorus range for depth is 50 - 200, so (1-4) * 50 with log scaling
        // Doppler should always be 1.f for chorus. Crazy range should be 0.95 - 1.05 to avoid artifacts.
        float depthFactor = (1.f - sqrt(depth)) * 3.f + 1.f;
        float lfoValue = lfo.tick(modulationWaveform); // -1 to 1
//        floatIndex += (lfoValue + 1.f) / (depthFactor * 50) + doppler * 0.05 + 1.f; // FIRST ONE IS DEPTH -- SECOND ONE IS DOPPLER EFFECT
        floatIndex += (lfoValue + 1.f) / (depthFactor * depthScale) + doppler * 0.05 + 1.f; // FIRST ONE IS DEPTH -- SECOND ONE IS DOPPLER EFFECT
        while (floatIndex >= bufferSize) {
            floatIndex -= bufferSize;
        }

        return readSample;
    }
};
