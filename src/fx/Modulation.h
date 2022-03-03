#pragma once
#include "../chorus/Lfo.h"
#include "../delay/AudioBuffer.h"


// We are starting here already at a 600 sample delay. Adding 1450 takes us to 2050, which is 50ms. +300 samples is @20.4 ms. 20-50 is a typical chorus range.
// Adding 300 or higher sample delay to the main delay line or whatever based on a param to get into chorus sound range. No extra delay is a longish delay flanger
const int MIN_MODULATION_DELAY = 0;
const int MAX_MODULATION_DELAY = 1200;
const int MODULATION_BUFFER_SIZE = MAX_MODULATION_DELAY + 1;


class Modulation : public WriteInsert {
protected:
    Lfo lfo;
    float floatIndex = (MIN_MODULATION_DELAY + MAX_MODULATION_DELAY) / 2;
    int writeIndex = 0;
    int modulationBuffer[MODULATION_BUFFER_SIZE];

public:
    float depth = 0.5f; // delay range from 0.f to 1.fs 
    float rate = 1.f; // in Hz
    float doppler = 0.f; // -1.f to 1.f
    int modulationWaveform = 0;


    Modulation() :
        lfo(44100.f)
    {
        lfo.setWaveform(0);
        lfo.setRate(rate);
        memset(modulationBuffer, 0, MODULATION_BUFFER_SIZE * sizeof(int));
    }


    int16_t processSample(int16_t sample) override {
        modulationBuffer[writeIndex] = sample;

        int curIndex = (int)floor(floatIndex);
        int nextIndex = curIndex + 1;
        if (nextIndex >= MODULATION_BUFFER_SIZE) {
            nextIndex -= MODULATION_BUFFER_SIZE;
        }
        double fractionalIndex = floatIndex - (double)curIndex;

        int16_t curSample = modulationBuffer[curIndex];
        int16_t nextSample = modulationBuffer[nextIndex];

        int16_t readSample = (int16_t)((1 - fractionalIndex) * curSample + fractionalIndex * nextSample);

        writeIndex++;
        if (writeIndex >= MODULATION_BUFFER_SIZE) {
            writeIndex -= MODULATION_BUFFER_SIZE;
        }

        float lfoValue = lfo.tick(modulationWaveform); // -1 to 1
        floatIndex += (lfoValue + 1) / 88 + 0.99; // FIRST ONE IS DEPTH -- SECOND ONE IS DOPPLER EFFECT
//        floatIndex += (lfoValue + 1) / 170 + 1.f; // FIRST ONE IS DEPTH -- SECOND ONE IS DOPPLER EFFECT
//        floatIndex += (lfoValue + 1) / 85 + 0.95; // FIRST ONE IS DEPTH -- SECOND ONE IS DOPPLER EFFECT
        while (floatIndex >= MODULATION_BUFFER_SIZE) {
            floatIndex -= MODULATION_BUFFER_SIZE;
        }

        return readSample;
    }
};
