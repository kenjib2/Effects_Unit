#pragma once
#include "../chorus/Lfo.h"
#include "../delay/AudioBuffer.h"


const int MIN_CHORUS_DELAY_LENGTH = 820;
const int MAX_CHORUS_DELAY_LENGTH = 2050;
const int MODULATION_BUFFER_SIZE = MAX_CHORUS_DELAY_LENGTH + 1;


class Modulation : public WriteInsert {
protected:
    Lfo lfo;
    float floatIndex = 0.f;
    int writeIndex = 0;
    int modulationBuffer[MODULATION_BUFFER_SIZE];

public:
    float depth = 0.5f; // volume from 0.f to 1.fs 
    float rate = 1.f; // in Hz


    Modulation() :
        lfo(44100.f)
    {
        lfo.setWaveform(0);
        lfo.setRate(rate);
    }


    int16_t processSample(int16_t sample) override {
        modulationBuffer[writeIndex] = sample;
        writeIndex++;
        while (writeIndex >= MODULATION_BUFFER_SIZE) {
            writeIndex -= MODULATION_BUFFER_SIZE;
        }

        return sample;
    }
};
